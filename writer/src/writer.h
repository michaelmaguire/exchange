

#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

class Writer {

public:

	Writer();
	~Writer();
	void setup(unsigned short port);
	void send(const std::string & data);
private:

	boost::asio::io_service _ioService;

	boost::asio::ip::udp::socket _socket;

	boost::asio::ip::udp::endpoint _endpoint;

	boost::log::sources::severity_logger< boost::log::trivial::severity_level > _lg;

};
