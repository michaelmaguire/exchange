//============================================================================
// Name        : reader.cpp
// Author      : michaelmaguire
// Version     :
// Copyright   : Copyright michaelmaguire
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

GTEST_API_ int main(int argc, char **argv) {
	cout << "argc[" << argc << "]" << endl;
	if( argc > 0 ) {
		cout << "argv[0][" << argv[0] << "]" << endl;
	}
	if( argc > 1 ) {
		cout << "argv[1][" << argv[1] << "]" << endl;
		if( 0 == strcmp(argv[1], "--test" ) ) {
			cout << "Running main() from reader.cpp RUN_ALL_TESTS\n" << endl;
			testing::InitGoogleTest(&argc, argv);
			int returnValue = RUN_ALL_TESTS();
			cout << "Running main() from reader.cpp RUN_ALL_TESTS returnValue[" << returnValue << "]\n" << endl;
			return returnValue;
		}
	}

	return 0;
}

TEST(IntegerInputsSuite, simpleSum)
{
  //first, set up any inputs to your
  const int SIZE = 3;
  double arr[SIZE]  = {1, 2, 3};
  //then, make an assertion to test
  EXPECT_EQ(arr[1], 2) << "The sum is not correct";
  EXPECT_EQ(arr[1], 3) << "The sum is not correct";
}
