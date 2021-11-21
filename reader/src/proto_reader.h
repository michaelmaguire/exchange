/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef PROTO_READER_H_
#define PROTO_READER_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include "order.pb.h"

class ProtoReader {

public:

	static const size_t max_buffer_size = 1024;

	ProtoReader();
	virtual void setup(unsigned short listenPort);
	virtual void run();
	virtual ~ProtoReader();

protected:
	// Override this to implement your protobuffer read handling.
	virtual void do_read(const exchange::ExchangeMessage &exchangeMessage) {
	}
	;

	mutable boost::log::sources::severity_logger<
			boost::log::trivial::severity_level> _lg;

	virtual void start_receive();
	virtual void handle_receive(const boost::system::error_code &e,
			std::size_t bytes_transferred);

	boost::asio::io_service _ioService;

	boost::asio::ip::udp::socket _socket;

	boost::array<char, max_buffer_size> _receive_buffer;

};

#endif /* PROTO_READER_H_ */
