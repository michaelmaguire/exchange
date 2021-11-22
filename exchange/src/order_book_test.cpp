/*
 * Copyright: 2021, Michael Maguire
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "order_book.h"

using ::testing::AtLeast;

class MockConfirmationsCallback: public ConfirmationsCallback {
public:
	MOCK_METHOD(void, sendOrderAcknowledgement, (uint32_t user, uint32_t userOrder), (override));
	MOCK_METHOD(void, sendTradeConfirmation, (uint32_t useridbuy,
					uint32_t userorderidbuy, uint32_t useridsell,
					uint32_t userorderidsell, uint32_t price, uint32_t quantity,
					std::string symbol), (override) );
	MOCK_METHOD(void, sendTopOfBookChange, (bool buy, uint32_t price,
					uint32_t quantity, bool sideElimination), (override) );
};

TEST(OrderBookSuite, simpleAdd) {

	MockConfirmationsCallback confirmationsCallback;
	OrderBook orderBook(&confirmationsCallback, "IBM");

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

	MockConfirmationsCallback confirmationsCallback;
	OrderBook orderBook(&confirmationsCallback, "AAPL");

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

TEST(OrderBookSuite, simpleAddThenMarket) {

	MockConfirmationsCallback confirmationsCallback;
	EXPECT_CALL(confirmationsCallback, sendTradeConfirmation).Times(AtLeast(1));

	OrderBook orderBook(&confirmationsCallback, "AAPL");

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

	Order order3(Order::BUY, 0, 100, 7, 1900);
	orderBook.addOrder(order3);


}
