#include "reader.h"


using boost::asio::ip::udp;
using namespace boost::log::trivial;


Reader::Reader() : _ioService(), _socket(_ioService){

}


void Reader::setup(unsigned short port) {

	boost::system::error_code e;

	udp::endpoint endpoint = udp::endpoint(boost::asio::ip::address_v4::any(), port);

	_socket.connect(endpoint, e);
	if( e ) {
		BOOST_LOG_SEV(_lg, error) << "Reader::setup error _socket.connect[" << e.message() << "]";
	}
	else {
		BOOST_LOG_SEV(_lg, info) << "Reader::setup _socket.connect";
	}
}

Reader::~Reader()
{
	boost::system::error_code e;
	_socket.close(e);

	if( e ){
		BOOST_LOG_SEV(_lg, error) << "Reader::~Reader error _socket.close[" << e.message() << "]";
	} else {
		BOOST_LOG_SEV(_lg, info) << "Reader::~Reader _socket.close";

	}
}

void Reader::receive(std::string & data) {

	boost::system::error_code e;
	boost::asio::socket_base::message_flags flags = {0};

	// A separate, writeable endpoint will be filled by receive_from
	udp::endpoint endpoint;
    std::size_t bytes_transferred = _socket.receive_from(boost::asio::buffer(data), endpoint, flags, e);

	if( e ){
		BOOST_LOG_SEV(_lg, error) << "Reader::send error _socket.receive_from[" << e.message() << "]";
	} else if ( bytes_transferred > 0 ) {
		BOOST_LOG_SEV(_lg, info) << "Reader::send  _socket.receive_from bytes_transferred["<< bytes_transferred << "] data[" << data << "]";
	}


}

