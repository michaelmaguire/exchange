/*
 * Copyright: 2021, Michael Maguire
 */

#include <gtest/gtest.h>

#include "order_book.h"

TEST(OrderBookSuite, simpleAdd) {

	ConfirmationsCallback confirmationsCallback;
	OrderBook orderBook(&confirmationsCallback);

	Order order1(Order::BUY, 10, 100, 1, 1);
	orderBook.addOrder(order1);

	Order order2(Order::SELL, 11, 100, 2, 1);
	orderBook.addOrder(order2);

	std::pair<Order, Order> top = orderBook.top();
	EXPECT_EQ(top.first._side, Order::BUY);
	EXPECT_EQ(top.first._price, 10);
	EXPECT_EQ(top.first._quantity, 100);
	EXPECT_EQ(top.second._side, Order::SELL);
	EXPECT_EQ(top.second._price, 11);
	EXPECT_EQ(top.second._quantity, 100);

}

TEST(OrderBookSuite, simpleAddThenCancel) {

	ConfirmationsCallback confirmationsCallback;
	OrderBook orderBook(&confirmationsCallback);

	Order order1(Order::BUY, 10, 100, 7, 1900);
	orderBook.addOrder(order1);

	Order order2(Order::SELL, 11, 100, 13, 2100);
	orderBook.addOrder(order2);

	std::pair<Order, Order> top = orderBook.top();
	EXPECT_EQ(top.first._side, Order::BUY);
	EXPECT_EQ(top.first._price, 10);
	EXPECT_EQ(top.first._quantity, 100);
	EXPECT_EQ(top.first._user, 7);
	EXPECT_EQ(top.first._userOrder, 1900);
	EXPECT_EQ(top.second._side, Order::SELL);
	EXPECT_EQ(top.second._price, 11);
	EXPECT_EQ(top.second._quantity, 100);
	EXPECT_EQ(top.second._user, 13);
	EXPECT_EQ(top.second._userOrder, 2100);

	EXPECT_EQ(false, orderBook.cancelOrder(8, 1900));
	EXPECT_EQ(false, orderBook.cancelOrder(7, 1800));
	EXPECT_EQ(true, orderBook.cancelOrder(7, 1900));

	EXPECT_EQ(false, orderBook.cancelOrder(8, 2100));
	EXPECT_EQ(false, orderBook.cancelOrder(13, 2000));
	EXPECT_EQ(true, orderBook.cancelOrder(13, 2100));

}
