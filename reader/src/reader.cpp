//============================================================================
// Name        : reader.cpp
// Author      : michaelmaguire
// Version     :
// Copyright   : Copyright michaelmaguire
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

GTEST_API_ int main(int argc, char **argv) {
        printf("Running main() from gtest_main.cc\n");
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
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
