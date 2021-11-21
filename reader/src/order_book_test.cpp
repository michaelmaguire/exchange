/*
 * Copyright: 2021, Michael Maguire
 */

#include <gtest/gtest.h>

#include "order_book.h"

TEST(OrderBookSuite, simpleAdd) {

	OrderBook orderBook;
	orderBook.addOrder(true /*buy*/, 10, 100, 1, 1);
	orderBook.addOrder(false /*sell*/, 11, 100, 1, 1);

}

