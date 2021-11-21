/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book_reader.h"

OrderBookReader::OrderBookReader(unsigned short port, const std::string symbol) :
		ProtoReader(port), _symbol(symbol) {

}

OrderBookReader::~OrderBookReader() {
}

void OrderBookReader::do_read(exchange::ExchangeMessage &exchangeMessage) {

}

