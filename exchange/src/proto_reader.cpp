/*
 * Copyright: 2021, Michael Maguire
 */

#include <boost/bind/bind.hpp>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "proto_reader.h"

using boost::asio::ip::udp;
using namespace boost::log::trivial;

ProtoReader::ProtoReader() :
		_ioService(), _socket(_ioService) {

	BOOST_LOG_SEV(_lg, trace)
	<< "ProtoReader::ProtoReader constructor";

}

void ProtoReader::setup(unsigned short listenPort) {

	BOOST_LOG_SEV(_lg, trace)
	<< "ProtoReader::ProtoReader setup";

	// Create the socket so that multiple may be bound to the same address.
	boost::asio::ip::udp::endpoint listenEndpoint(
			boost::asio::ip::address::from_string("0.0.0.0"), listenPort);
	_socket.open(listenEndpoint.protocol());
	_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
	_socket.bind(listenEndpoint);

	// Join the multicast group.
	_socket.set_option(
			boost::asio::ip::multicast::join_group(
					boost::asio::ip::address::from_string("239.255.0.1")));

	start_receive();

}

ProtoReader::~ProtoReader() {
	boost::system::error_code e;
	_socket.close(e);

	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Reader::~Reader error _socket.close[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, trace)
		<< "Reader::~Reader _socket.close";
	}
}

void ProtoReader::run() {
	boost::system::error_code e;
	_ioService.run(e);
	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Reader::run error[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, trace)
		<< "Reader::run exited normally";
	}
}

void ProtoReader::start_receive() {

	boost::asio::ip::udp::endpoint endpoint;

	_socket.async_receive_from(boost::asio::buffer(_receive_buffer), endpoint,
			boost::bind(&ProtoReader::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}

void ProtoReader::handle_receive(const boost::system::error_code &e,
		std::size_t bytes_transferred) {
	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Reader::handle_receive [" << bytes_transferred << "] error["
				<< e.message() << "]";
	}
	if (!e || e == boost::asio::error::message_size) {
		BOOST_LOG_SEV(_lg, trace)
		<< "Reader::handle_receive [" << bytes_transferred << "] error["
				<< e.message() << "]";
		_receive_buffer[bytes_transferred] = '\0';

		const ::google::protobuf::uint32 PACKET_MAGIC = 6664; // rudimentary packet identification
		const ::google::protobuf::uint32 PACKET_VERSION = 1; // room to grow

		google::protobuf::io::ArrayInputStream arrayInputStream(
				_receive_buffer.data(), max_buffer_size);
		google::protobuf::io::CodedInputStream codedInputStream(
				&arrayInputStream);

		::google::protobuf::uint32 packetMagic;
		codedInputStream.ReadLittleEndian32(&packetMagic);
		if (PACKET_MAGIC != packetMagic) {
			BOOST_LOG_SEV(_lg, error)
			<< "Reader::handle_receive received bad packetMagic[" << packetMagic
					<< "]";
		} else {

			::google::protobuf::uint32 packetVersion;
			codedInputStream.ReadLittleEndian32(&packetVersion);
			if (PACKET_VERSION != packetVersion) {
				BOOST_LOG_SEV(_lg, error)
				<< "Reader::handle_receive received bad packetVersion["
						<< packetVersion << "]";
			} else {

				::google::protobuf::uint32 messageSize;
				codedInputStream.ReadVarint32(&messageSize);
				if ((sizeof(PACKET_MAGIC) + sizeof(PACKET_VERSION) + messageSize)
						> bytes_transferred) {
					BOOST_LOG_SEV(_lg, error)
					<< "Reader::handle_receive received incomplete packet";
				} else {

					exchange::ExchangeMessage exchangeMessage;
					exchangeMessage.ParseFromCodedStream(&codedInputStream);

					BOOST_LOG_SEV(_lg, trace)
					<< "Reader::handle_receive command_case["
							<< exchangeMessage.command_case()
							<< "] messageSize[" << messageSize
							<< "] _receive_buffer["
							<< exchangeMessage.DebugString() << "]";

					// Call subclass' do_read implementation.
					do_read(exchangeMessage);
				}
			}
		}

		start_receive();
	}
}

