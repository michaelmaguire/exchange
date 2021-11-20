/*
 * main.cpp
 *
 *  Created on: 20 Nov 2021
 *      Author: michaelmaguire
 */


#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost::log::trivial;

void init_logging(const std::string & filename)
{
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
}


GTEST_API_ int main(int argc, char **argv) {
	if( argc > 0 ) {
	    BOOST_LOG_TRIVIAL(trace) << "argv[0][" << argv[0] << "]";
	}
	init_logging("reader");

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

	return 0;
}


