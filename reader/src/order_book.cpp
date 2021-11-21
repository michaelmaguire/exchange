/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book.h"
using namespace boost::log::trivial;

Order::Order(Side side, uint32_t price, uint32_t quantity, uint32_t user,
		uint32_t userOrder) :
		_side(side), _price(price), _quantity(quantity), _user(user), _userOrder(
				userOrder) {
}

Order::Order(Side side, uint32_t price, const Quantity &q) :
		_side(side), _price(price), _quantity(q._quantity), _user(q._user), _userOrder(
				q._userOrder) {

}

Order::~Order() {

}

std::ostream& operator<<(std::ostream &os, const Order::Side &s) {
	if (Order::Side::BUY == s) {
		os << "BUY";
	} else {
		os << "SELL";
	}
	return os;
}

std::ostream& operator<<(std::ostream &os, const Order &o) {
	os << "{ \"side\":\"" << o._side << "\", \"price\":\"" << o._price
			<< "\",\"quantity\":\"" << o._quantity << "\",\"user\":\""
			<< o._user << "\",\"userOrder\":\"" << o._userOrder << "\"}";
	return os;
}

Quantity::Quantity(uint32_t quantity, uint32_t user, uint32_t userOrder) :
		_quantity(quantity), _user(user), _userOrder(userOrder) {
}

Quantity::~Quantity() {

}

std::ostream& operator<<(std::ostream &os, const Quantity &q) {
	os << "{ \"quantity\":\"" << q._quantity << "\",\"user\":\"" << q._user
			<< "\",\"userOrder\":\"" << q._userOrder << "\"}";
	return os;
}

PriceLevel::PriceLevel(uint32_t price) :
		_price(price) {
}

PriceLevel::~PriceLevel() {

}

std::ostream& operator<<(std::ostream &os, const PriceLevel &pl) {
	os << "{ \"price\":\"" << pl._price << "\",\"quantities\":[";
	bool first = true;
	for (auto it = pl._quantitiesInTimeOrder.begin();
			it != pl._quantitiesInTimeOrder.end(); ++it) {

		if (!first) {
			os << ",";
		}
		first = false;

		os << *it;
	}
	os << "]}";
	return os;
}

void PriceLevel::addQuantity(uint32_t quantity, uint32_t user,
		uint32_t userOrder) {
	Quantity quantityEntry(quantity, user, userOrder);
	_quantitiesInTimeOrder.push_back(quantityEntry);
}

Quantity& PriceLevel::front() {
	return _quantitiesInTimeOrder.front();
}

Quantity& PriceLevel::back() {
	return _quantitiesInTimeOrder.back();
}

OrderBook::OrderBook() {
}

OrderBook::~OrderBook() {
}

std::ostream& operator<<(std::ostream &os, const OrderBook &ob) {

	bool first = true;
	os << "{ \"buyOrders\":[";
	for (auto it = ob._buyOrders.begin(); it != ob._buyOrders.end(); ++it) {

		if (!first) {
			os << ",";
		}
		first = false;

		os << it->second;
	}

	first = true;
	os << "], \"sellOrders\":[";
	for (auto it = ob._sellOrders.begin(); it != ob._sellOrders.end(); ++it) {

		if (!first) {
			os << ",";
		}
		first = false;

		os << it->second;
	}
	os << "]}";
	return os;
}

void OrderBook::addOrder(const Order &order) {

	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::addOrder before add [" << *this << "]";

	ORDERS_TYPE *orders = &_sellOrders;
	if (Order::Side::BUY == order._side) {
		orders = &_buyOrders;
	}

	// See if PriceLevel already exists
	auto it = orders->find(order._price);
	if (it != orders->end()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBook::addOrder PriceLevel price[" << order._price
				<< "] already exists, add new order[" << order << "]";
		it->second.addQuantity(order._quantity, order._user, order._userOrder);
	} else {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBook::addOrder PriceLevel price[" << order._price
				<< "] doesn't already exists, creating with new order[" << order
				<< "]";
		PriceLevel priceLevel(order._price);
		priceLevel.addQuantity(order._quantity, order._user, order._userOrder);
		orders->emplace(order._price, priceLevel);
	}

	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::addOrder after add [" << *this << "]";

}

void OrderBook::cancelOrder(uint32_t user, uint32_t userOrder) {

}

void OrderBook::flush() {
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::flush before flush [" << *this << "]";

	_buyOrders.clear();
	_sellOrders.clear();

	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::flush after flush [" << *this << "]";
}

// Returns the top of the order book, first BYE, second SELL.
const std::pair<Order, Order> OrderBook::top() const {

	if (0 == _buyOrders.size()) {
		throw std::out_of_range("No buy orders yet");
	}
	if (0 == _sellOrders.size()) {
		throw std::out_of_range("No sell orders yet");
	}

	// Take advantage of  map's ordering guarantee, given that price is our key.
	auto topByePriceLevel = _buyOrders.begin()->second;
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::top topByePriceLevel[" << topByePriceLevel << "]";

	auto topSellPriceLevel = _sellOrders.rbegin()->second;
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::top topSellPriceLevel[" << topSellPriceLevel << "]";

	auto topBuyFirstInTimeQuantity = topByePriceLevel.front();
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::top topBuyFirstInTimeQuantity[" << topBuyFirstInTimeQuantity
			<< "]";
	auto topSellFirstInTimeQuantity = topSellPriceLevel.front();
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::top topSellFirstInTimeQuantity["
			<< topSellFirstInTimeQuantity << "]";

	Order topBye(Order::BUY, topByePriceLevel._price,
			topBuyFirstInTimeQuantity);
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::top topBye[" << topBye << "]";
	Order topSell(Order::SELL, topSellPriceLevel._price,
			topSellFirstInTimeQuantity);
	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::top topSell[" << topSell << "]";

	return std::make_pair(topBye, topSell);

}

void OrderBook::cross() {

}

