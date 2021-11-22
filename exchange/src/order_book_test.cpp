/*
 * Copyright: 2021, Michael Maguire
 */

#include <gtest/gtest.h>

#include "order_book.h"

TEST(OrderBookSuite, simpleAdd) {

	OrderBook orderBook;

	Order order1(Order::BUY, 10, 100, 1, 1);
	orderBook.addOrder(order1);

	Order order2(Order::SELL, 11, 100, 1, 1);
	orderBook.addOrder(order2);

	std::pair<Order, Order> top = orderBook.top();
	EXPECT_EQ(top.first._side, Order::BUY);
	EXPECT_EQ(top.first._price, 10);
	EXPECT_EQ(top.first._quantity, 100);
	EXPECT_EQ(top.second._side, Order::SELL);
	EXPECT_EQ(top.second._price, 11);
	EXPECT_EQ(top.second._quantity, 100);

}

