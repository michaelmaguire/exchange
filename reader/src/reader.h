/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef READER_H_
#define READER_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

class Reader {

public:

	static const size_t max_buffer_size = 1024;

	explicit Reader(unsigned short port);
	void run();
	~Reader();
private:
	void start_receive();
	void handle_receive(const boost::system::error_code &e,
			std::size_t bytes_transferred);

	boost::asio::io_service _ioService;

	boost::asio::ip::udp::socket _socket;

	mutable boost::log::sources::severity_logger<
			boost::log::trivial::severity_level> _lg;

	boost::array<char, max_buffer_size> _receive_buffer;

};

#endif /* READER_H_ */
