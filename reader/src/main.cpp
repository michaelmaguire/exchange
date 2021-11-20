/*
 * main.cpp
 *
 *  Created on: 20 Nov 2021
 *      Author: michaelmaguire
 */


#include <iostream>
#include <boost/log/trivial.hpp>
#include <gtest/gtest.h>

using namespace std;

#if 0
void init_logging()
{
    logging::add_file_log("sample.log");

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}
#endif


GTEST_API_ int main(int argc, char **argv) {
	//init_logging();
	cout << "argc[" << argc << "]" << endl;
	if( argc > 0 ) {
	    BOOST_LOG_TRIVIAL(trace) << "argv[0][" << argv[0] << "]";
	}
	if( argc > 1 ) {
		cout << "argv[1][" << argv[1] << "]" << endl;
		if( 0 == strcmp(argv[1], "--test" ) ) {
			cout << "Running " << argv[0] << " main() from main.cpp RUN_ALL_TESTS starting\n" << endl;
			testing::InitGoogleTest(&argc, argv);
			int returnValue = RUN_ALL_TESTS();
			cout << "Running " << argv[0] << " main() from main.cpp RUN_ALL_TESTS returnValue[" << returnValue << "]\n" << endl;
			return returnValue;
		}
	}

	return 0;
}


