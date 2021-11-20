#include "reader.h"

#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;
using namespace boost::log::trivial;

Reader::Reader(unsigned short port) :
		_ioService(), _socket(_ioService, udp::endpoint(udp::v4(), port)) {

	start_receive();

}

Reader::~Reader() {
	boost::system::error_code e;
	_socket.close(e);

	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Reader::~Reader error _socket.close[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, info)
		<< "Reader::~Reader _socket.close";
	}
}

void Reader::run() {
	boost::system::error_code e;
	_ioService.run(e);
	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Reader::run error[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, info)
		<< "Reader::run exited normally";
	}
}

void Reader::start_receive() {

	boost::asio::ip::udp::endpoint endpoint;

	_socket.async_receive_from(boost::asio::buffer(_receive_buffer), endpoint,
			boost::bind(&Reader::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}

void Reader::handle_receive(const boost::system::error_code &e,
		std::size_t bytes_transferred) {
	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Reader::handle_receive [" << bytes_transferred << "] error["
				<< e.message() << "]";
	}
	if (!e || e == boost::asio::error::message_size) {

		std::string message(_receive_buffer.begin(),
				_receive_buffer.begin() + bytes_transferred);

		BOOST_LOG_SEV(_lg, info)
		<< "Reader::handle_receive [" << bytes_transferred
				<< "] _receive_buffer[" << message << "]";

		start_receive();
	}
}

