/*
 * Copyright: 2021, Michael Maguire
 */

#include "writer.h"

using boost::asio::ip::udp;
using namespace boost::log::trivial;

Writer::Writer(unsigned short port) :
		_ioService(), _socket(_ioService) {

	boost::system::error_code e;

	_socket.open(udp::v4(), e);
	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Writer::setup error _socket.open[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, trace)
		<< "Writer::setup _socket.open";
		_socket.set_option(udp::socket::reuse_address(true));
		_socket.set_option(boost::asio::socket_base::broadcast(true));

		_endpoint = udp::endpoint(boost::asio::ip::address_v4::broadcast(),
				port);
	}
}

Writer::~Writer() {
	boost::system::error_code e;
	_socket.close(e);

	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Writer::~Writer error _socket.close[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, trace)
		<< "Writer::~Writer _socket.close";

	}
}

void Writer::send(boost::asio::streambuf &output_streambuf_to_send) {

	boost::system::error_code e;
	boost::asio::socket_base::message_flags flags = { 0 };

	std::size_t sizeSent = _socket.send_to(output_streambuf_to_send.data(),
			_endpoint, flags, e);

	if (e) {
		BOOST_LOG_SEV(_lg, error)
		<< "Writer::send error _socket.send_to[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, trace)
		<< "Writer::send  _socket.send_to sizeSent[" << sizeSent << "]";
	}

}

