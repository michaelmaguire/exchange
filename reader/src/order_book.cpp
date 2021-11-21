/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book.h"
using namespace boost::log::trivial;

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

void OrderBook::addOrder(bool isBuy, uint32_t price, uint32_t quantity,
		uint32_t user, uint32_t userOrder) {

	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::addOrder before add [" << *this << "]";

	ORDERS_TYPE * orders = & _sellOrders;
	if (isBuy) {
		orders = & _buyOrders;
	}

	// See if PriceLevel already exists
	auto it = orders->find(price);
	if (it != orders->end()) {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBook::addOrder PriceLevel price[" << price
				<< "] already exists, add new quantity[" << quantity << "]";
		it->second.addQuantity(quantity, user, userOrder);
	} else {
		BOOST_LOG_SEV(_lg, info)
		<< "OrderBook::addOrder PriceLevel price[" << price
				<< "] doesn't already exists, creating with new quantity["
				<< quantity << "]";
		PriceLevel priceLevel(price);
		priceLevel.addQuantity(quantity, user, userOrder);
		orders->emplace(price, priceLevel);
	}

	BOOST_LOG_SEV(_lg, info)
	<< "OrderBook::addOrder after add [" << *this << "]";

}

