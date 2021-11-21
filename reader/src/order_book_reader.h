/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef ORDER_BOOK_READER_H_
#define ORDER_BOOK_READER_H_

#include "proto_reader.h"

class OrderBookReader: public ProtoReader {
public:
	OrderBookReader(unsigned short port, const std::string symbol);
	virtual ~OrderBookReader();

protected:
	virtual void do_read(exchange::ExchangeMessage &exchangeMessage);

private:
	std::string _symbol;
};

#endif /* ORDER_BOOK_READER_H_ */
