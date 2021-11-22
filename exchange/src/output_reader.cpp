/*
 * Copyright: 2021, Michael Maguire
 */

#include "output_reader.h"

using namespace boost::log::trivial;

OutputReader::OutputReader() {

	BOOST_LOG_SEV(_lg, info)
	<< "OutputReader::OutputReader constructor";

}

OutputReader::~OutputReader() {
}

void OutputReader::do_read(const exchange::ExchangeMessage &exchangeMessage) {

	if (exchangeMessage.has_orderacknowledgement()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OutputReader::do_read handling orderacknowledgement";

		auto oa = exchangeMessage.orderacknowledgement();

		std::cout << "A," << oa.user() << "," << oa.userorder() << "\n";

	} else if (exchangeMessage.has_tradeconfirmation()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OutputReader::do_read handling tradeconfirmation";

		auto tc = exchangeMessage.tradeconfirmation();

		std::cout << "T," << tc.useridbuy() << "," << tc.userorderidbuy() << ","
				<< tc.useridsell() << "," << tc.userorderidsell() << ","
				<< tc.price() << "," << tc.quantity() << "\n";

	} else if (exchangeMessage.has_topofbookchange()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OutputReader::do_read handling topofbookchange";

		auto top = exchangeMessage.topofbookchange();

		std::cout << "B,";
		if (top.side() == top.BUY) {
			std::cout << "B";
		} else {
			std::cout << "S";
		}

		if (top.sideelimination()) {
			std::cout << ",-,-\n";
		} else {
			std::cout << "," << top.price() << "," << top.quantity() << "\n";
		}

	} else {

		BOOST_LOG_SEV(_lg, info)
		<< "OutputReader::do_read ignoring this message type";

	}
}

