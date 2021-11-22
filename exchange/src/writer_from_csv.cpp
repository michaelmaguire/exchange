/*
 * Copyright: 2021, Michael Maguire
 */

#include "writer_from_csv.h"

#include "boost/algorithm/string.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include <string>

#include "order.pb.h"

using namespace boost::log::trivial;

extern uint64_t g_sequenceNumber;

WriterFromCSV::WriterFromCSV(unsigned short port) :
		ProtoWriter(port) {

}

WriterFromCSV::~WriterFromCSV() {
}

void WriterFromCSV::processLineTokens(const std::vector<std::string> &tokens) {

	if (tokens.size() == 0) {
		BOOST_LOG_SEV(_lg, error)
		<< "WriterFromCSV::processLineTokens invalid line";
		return;
	}
	std::string first = tokens[0];
	if (first.size() != 1) {
		BOOST_LOG_SEV(_lg, error)
		<< "WriterFromCSV::processLineTokens invalid command";
	}
	char command = first[0];

	switch (command) {
	case 'N':
		if (tokens.size() != 7) {
			BOOST_LOG_SEV(_lg, error)
					<< "WriterFromCSV::processLineTokens invalid number of tokens for N";
		} else {
			uint32_t user = stoul(tokens[1]);
			std::string symbol = tokens[2];
			uint32_t price = stoul(tokens[3]);
			uint32_t quantity = stoul(tokens[4]);
			std::string side = tokens[5];
			uint32_t userOrder = stoul(tokens[6]);

			exchange::ExchangeMessage exchangeMessage;
			exchangeMessage.set_sequencenumber(g_sequenceNumber++);
			auto newOrder = new exchange::NewOrder();
			newOrder->set_user(user);
			newOrder->set_symbol(symbol);
			newOrder->set_price(price);
			newOrder->set_quantity(quantity);

			if (side[0] == 'B') {
				newOrder->set_side(exchange::NewOrder::BUY);
			} else {
				newOrder->set_side(exchange::NewOrder::SELL);
			}

			newOrder->set_userorder(userOrder);
			exchangeMessage.set_allocated_neworder(newOrder);
			send(exchangeMessage);

		}
		break;
	case 'C':
		if (tokens.size() != 3) {
			BOOST_LOG_SEV(_lg, error)
					<< "WriterFromCSV::processLineTokens invalid number of tokens for C";
		} else {
			uint32_t user = stoul(tokens[1]);
			uint32_t userOrder = stoul(tokens[2]);

			exchange::ExchangeMessage exchangeMessage;
			exchangeMessage.set_sequencenumber(g_sequenceNumber++);
			auto cancelOrder = new exchange::CancelOrder();
			cancelOrder->set_user(user);
			cancelOrder->set_userorder(userOrder);
			exchangeMessage.set_allocated_cancelorder(cancelOrder);
			send(exchangeMessage);

		}
		break;
	case 'F':

	{
		exchange::ExchangeMessage exchangeMessage;
		exchangeMessage.set_sequencenumber(g_sequenceNumber++);
		auto flushOrder = new exchange::FlushOrder();
		exchangeMessage.set_allocated_flushorder(flushOrder);
		send(exchangeMessage);
	}
		break;
	default:
		BOOST_LOG_SEV(_lg, error)
		<< "WriterFromCSV::processLineTokens unrecognized line";
	}

}

void WriterFromCSV::loadAndWriteFile(const std::string &filename) {

	boost::filesystem::path filePath(filename);
	boost::filesystem::ifstream fileHandler(filePath);
	std::string line;
	while (std::getline(fileHandler, line)) {

		// Only process if line doesn't begin with a '#' comment
		if (line.rfind("#", 0) == 0) {
			BOOST_LOG_SEV(_lg, trace)
			<< "WriterFromCSV::loadAndWriteFile ignoring comment line[" << line
					<< "]";
		} else {
			BOOST_LOG_SEV(_lg, trace)
			<< "WriterFromCSV::loadAndWriteFile parsing          line[" << line
					<< "]";

			// Thanks to https://bravenewmethod.com/2016/09/17/quick-and-robust-c-csv-reader-with-boost/ for this regex
			const boost::regex fieldsregx(
					",(?=(?:[^\"]*\"[^\"]*\")*(?![^\"]*\"))");
			boost::sregex_token_iterator tokenIterator(line.begin(), line.end(),
					fieldsregx, -1);
			boost::sregex_token_iterator end;

			std::vector<std::string> tokens;
			while (tokenIterator != end) {
				std::string token = tokenIterator->str();
				++tokenIterator;
				boost::algorithm::trim(token);
				if (token.size() > 0) {
					tokens.push_back(token);
				}
			}

			if (tokens.size() == 0) {
				BOOST_LOG_SEV(_lg, trace)
				<< "WriterFromCSV::loadAndWriteFile ignoring empty line["
						<< line << "]";
			} else {
				std::ostringstream oss;
				for (auto it = tokens.begin(); it != tokens.end(); ++it) {
					oss << *it << ",";
				}
				BOOST_LOG_SEV(_lg, info)
				<< "WriterFromCSV::loadAndWriteFile parsed " << tokens.size()
						<< " tokens[" << oss.str() << "]";

				processLineTokens(tokens);

			}

		}
	}
}
