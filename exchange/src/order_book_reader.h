/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef ORDER_BOOK_READER_H_
#define ORDER_BOOK_READER_H_

#include "proto_reader.h"
#include "order_book.h"

class OrderBookReader: public ProtoReader {
public:
	OrderBookReader(const std::string symbol);
	virtual ~OrderBookReader();

protected:

	virtual void do_read(const exchange::ExchangeMessage &exchangeMessage);



private:
	std::string _symbol;

	OrderBook _orderBook;
};

#endif /* ORDER_BOOK_READER_H_ */
