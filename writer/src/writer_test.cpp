#include <gtest/gtest.h>

TEST(IntegerInputsSuite, simpleSum) {
	//first, set up any inputs to your
	const int SIZE = 3;
	double arr[SIZE] = { 1, 2, 3 };
	//then, make an assertion to test
	EXPECT_EQ(arr[1], 2) << "The sum is not correct";
	EXPECT_EQ(arr[1], 3) << "The sum is not correct";
}

