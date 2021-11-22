/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book_reader.h"

using namespace boost::log::trivial;

OrderBookReader::OrderBookReader(ConfirmationsCallback *confirmationsCallback,
		const std::string symbol) :
		_orderBook(confirmationsCallback, symbol), _symbol(symbol) {

	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBookReader::OrderBookReader constructor";

}

OrderBookReader::~OrderBookReader() {
}

void OrderBookReader::do_read(
		const exchange::ExchangeMessage &exchangeMessage) {

	if (exchangeMessage.has_neworder()) {
		BOOST_LOG_SEV(_lg, trace)
		<< "OrderBookReader::do_read handling neworder";

		auto n = exchangeMessage.neworder();

		if (n.symbol().compare(_symbol) == 0) {

			Order order((n.side() == n.BUY ? Order::BUY : Order::SELL),
					n.price(), n.quantity(), n.user(), n.userorder());
			_orderBook.addOrder(order);
		} else {
			BOOST_LOG_SEV(_lg, trace)
			<< "OrderBookReader::do_read this order is not for us";
		}

	} else if (exchangeMessage.has_cancelorder()) {
		BOOST_LOG_SEV(_lg, trace)
		<< "OrderBookReader::do_read handling cancelorder";

		auto c = exchangeMessage.cancelorder();
		_orderBook.cancelOrder(c.user(), c.userorder());

	} else if (exchangeMessage.has_flushorder()) {
		BOOST_LOG_SEV(_lg, trace)
		<< "OrderBookReader::do_read handling flushorder";

		auto f = exchangeMessage.flushorder();
		_orderBook.flush();

	} else {

		BOOST_LOG_SEV(_lg, trace)
		<< "OrderBookReader::do_read ignoring this message type";

	}
}

