/*
 * main.cpp
 *
 *  Created on: 20 Nov 2021
 *      Author: michaelmaguire
 */


#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <gtest/gtest.h>

#include "writer.h"

using namespace std;
using namespace boost::log::trivial;

void init_logging(int argc, char **argv)
{
	string filename = "default";
	if( argc > 0 ) {
		boost::filesystem::path p = argv[0];
		filename = p.stem().string();
	}
    BOOST_LOG_TRIVIAL(info) << "init_logging for app[" << filename << "]";

	boost::log::add_file_log
    (
    	boost::log::keywords::file_name = filename + "_%N.log",
		boost::log::keywords::rotation_size = 10 * 1024 * 1024,
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		boost::log::keywords::format = "[%TimeStamp% p[%ProcessID%] t[%ThreadID%]]: %Message%"
    );

    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );

    boost::log::add_common_attributes();

	boost::log::sources::severity_logger< boost::log::trivial::severity_level > lg;

	BOOST_LOG_SEV(lg, info) << "init_logging completed for filename[" << filename << "]";
}


GTEST_API_ int main(int argc, char **argv) {
	init_logging(argc, argv);

	boost::log::sources::severity_logger< boost::log::trivial::severity_level > lg;

	if( argc > 1 ) {
		BOOST_LOG_SEV(lg, info) << "argv[1][" << argv[1] << "]";
		if( 0 == strcmp(argv[1], "--test" ) ) {
			BOOST_LOG_SEV(lg, info) << "Running " << argv[0] << " main() from main.cpp RUN_ALL_TESTS starting\n";
			testing::InitGoogleTest(&argc, argv);
			int returnValue = RUN_ALL_TESTS();
			BOOST_LOG_SEV(lg, info) << "Running " << argv[0] << " main() from main.cpp RUN_ALL_TESTS returnValue[" << returnValue << "]\n";
			return returnValue;
		}
	}

	Writer writer;
	writer.setup(1234);
	writer.send("Hello1");
	writer.send("Hello2");
	writer.send("Hello3");
	writer.send("Hello4");

	return 0;
}


