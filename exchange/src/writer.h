/*
 * Copyright: 2021, Michael Maguire
 */

#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

class Writer {

public:

	explicit Writer(unsigned short port);
	~Writer();
	void send(boost::asio::streambuf &output_streambuf_to_send);

protected:

	mutable boost::log::sources::severity_logger<
			boost::log::trivial::severity_level> _lg;

private:

	boost::asio::io_service _ioService;

	boost::asio::ip::udp::socket _socket;

	boost::asio::ip::udp::endpoint _endpoint;

};
