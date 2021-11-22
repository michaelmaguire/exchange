/*
 * Copyright: 2021, Michael Maguire
 */

#include <iostream>

#include <boost/filesystem.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/config.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <gtest/gtest.h>

#include "order_book_reader.h"
#include "output_reader.h"
#include "writer_from_csv.h"

using namespace std;
using namespace boost::log::trivial;

void init_logging(const std::string &filename) {
	BOOST_LOG_TRIVIAL(info)
	<< "init_logging for app[" << filename << "]";

	auto sink = boost::log::add_file_log(
			boost::log::keywords::file_name = filename + "_%N.log",
			boost::log::keywords::rotation_size = 10 * 1024 * 1024,
			boost::log::keywords::time_based_rotation =
					boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
			boost::log::keywords::format =
					"[%TimeStamp% p[%ProcessID%] t[%ThreadID%]]: %Message%");

	boost::log::core::get()->set_filter(
			boost::log::trivial::severity >= boost::log::trivial::info);

	boost::log::add_console_log(std::cout, boost::log::keywords::format =
			">> %Message%");

	boost::log::add_common_attributes();

	boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

	BOOST_LOG_SEV(lg, info)
	<< "init_logging completed for filename[" << filename << "]";
	sink->flush();
}

unsigned short g_exchangeMulticastUdpPort = 1234;

uint64_t g_sequenceNumber = 0L;

int run_in_client_mode(const std::string &filename) {

	WriterFromCSV writerFromCVS(g_exchangeMulticastUdpPort);
	writerFromCVS.loadAndWriteFile(filename);

	return 1;
}

int run_in_order_book_mode(const std::string &symbol) {

	OrderBookReader orderBookReader(symbol);
	orderBookReader.setup(g_exchangeMulticastUdpPort);
	orderBookReader.run();

	return 1;
}

int run_in_output_mode() {

	boost::log::core::get()->set_filter(
			boost::log::trivial::severity >= boost::log::trivial::error);

	OutputReader outputReader;
	outputReader.setup(g_exchangeMulticastUdpPort);
	outputReader.run();

	return 1;
}

GTEST_API_ int main(int argc, char **argv) {
	int returnValue = 0;

	try {
		boost::program_options::options_description desc("Allowed options");
		desc.add_options()("help,h", "produce help message")("test",
				"run tests")("client", "run in client mode reading CSV")("book",
				"run in order book mode on symbol --symbol")("symbol",
				boost::program_options::value<std::string>(),
				"symbol to run order book for --book mode")("output",
				"run in output logger more")("port",
				boost::program_options::value<unsigned short>()->default_value(
						1234), "set multicast UDP port")("filename",
				boost::program_options::value<std::string>(),
				"path to .CSV for --client mode");

		boost::program_options::variables_map variablesMap;
		boost::program_options::store(
				boost::program_options::parse_command_line(argc, argv, desc),
				variablesMap);
		boost::program_options::notify(variablesMap);

		if (variablesMap.count("help")) {
			std::cout << desc << "\n";
			return 1;
		}

		if (variablesMap.count("port")) {
			g_exchangeMulticastUdpPort =
					variablesMap["port"].as<unsigned short>();
			BOOST_LOG_TRIVIAL(info)
			<< "In main() setting UDP multicast port["
					<< g_exchangeMulticastUdpPort << "]\n";
		}

		if (variablesMap.count("test")) {
			init_logging("test");

			BOOST_LOG_TRIVIAL(info)
			<< "In main() from main.cpp RUN_ALL_TESTS starting\n";
			testing::InitGoogleTest(&argc, argv);
			returnValue = RUN_ALL_TESTS();
			BOOST_LOG_TRIVIAL(info)
			<< "In main() from main.cpp RUN_ALL_TESTS returnValue["
					<< returnValue << "]\n";
		} else if (variablesMap.count("client")) {
			init_logging("client");
			if (variablesMap.count("filename")) {

				std::string filename =
						variablesMap["filename"].as<std::string>();

				BOOST_LOG_TRIVIAL(info)
				<< "In main() running as 'client' reader orders from filename["
						<< filename << "] broadcasting to UDP multicast port["
						<< g_exchangeMulticastUdpPort << "]\n";

				returnValue = run_in_client_mode(filename);

			} else {
				std::cerr << "--client mode is missing --filename option\n";
			}
		} else if (variablesMap.count("book")) {
			if (variablesMap.count("symbol")) {

				std::string symbol = variablesMap["symbol"].as<std::string>();
				init_logging("book_" + symbol);

				BOOST_LOG_TRIVIAL(info)
				<< "In main() running in order 'book' mode for symbol["
						<< symbol << "] reading from UDP multicast port["
						<< g_exchangeMulticastUdpPort << "]\n";

				returnValue = run_in_order_book_mode(symbol);

			} else {
				std::cerr << "--book mode is missing --symbol option\n";
			}
		} else if (variablesMap.count("output")) {
			init_logging("output");

			BOOST_LOG_TRIVIAL(info)
					<< "In main() running in 'output' mode reading from UDP multicast port["
					<< g_exchangeMulticastUdpPort << "]\n";

			returnValue = run_in_output_mode();

		} else {
			std::cerr << "Missing mode" << "\n";
			std::cerr << desc << "\n";
			return 1;
		}

	} catch (const std::exception &ex) {
		std::cerr << ex.what() << '\n';
		returnValue = -1;
	}

	BOOST_LOG_TRIVIAL(info)
	<< "main exiting";
	return returnValue;
}

