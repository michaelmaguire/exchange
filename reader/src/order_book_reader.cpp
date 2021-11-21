/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book_reader.h"

using namespace boost::log::trivial;

OrderBookReader::OrderBookReader(const std::string symbol) :
		_symbol(symbol) {

	BOOST_LOG_SEV(_lg, info)
	<< "OrderBookReader::OrderBookReader constructor";

}

OrderBookReader::~OrderBookReader() {
}

void OrderBookReader::do_read(
		const exchange::ExchangeMessage &exchangeMessage) {
	if (exchangeMessage.has_neworder()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBookReader::do_read handling neworder";

		auto n = exchangeMessage.neworder();
		Order order((n.side() == n.BUY ? Order::BUY : Order::SELL), n.price(),
				n.quantity(), n.user(), n.userorder());
		_orderBook.addOrder(order);

	} else if (exchangeMessage.has_cancelorder()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBookReader::do_read handling cancelorder";

		auto n = exchangeMessage.cancelorder();
		_orderBook.cancelOrder(n.user(), n.userorder());

	} else if (exchangeMessage.has_flushorder()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBookReader::do_read handling flushorder";

		_orderBook.flush();

	} else {

		BOOST_LOG_SEV(_lg, info)
		<< "OrderBookReader::do_read ignoring this message type";

	}
}

