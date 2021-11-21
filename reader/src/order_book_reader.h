/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef ORDER_BOOK_READER_H_
#define ORDER_BOOK_READER_H_

#include "proto_reader.h"
#include "order_book.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

class OrderBookReader: public ProtoReader {
public:
	OrderBookReader(unsigned short port, const std::string symbol);
	virtual ~OrderBookReader();

protected:
	virtual void do_read(exchange::ExchangeMessage &exchangeMessage);

private:
	std::string _symbol;

	mutable boost::log::sources::severity_logger<boost::log::trivial::severity_level> _lg;

	OrderBook _orderBook;
};

#endif /* ORDER_BOOK_READER_H_ */
