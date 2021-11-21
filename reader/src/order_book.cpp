/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book.h"

Quantity::Quantity(uint32_t quantity, uint32_t user, uint32_t userOrder) :
		_quantity(quantity), _user(user), _userOrder(userOrder) {
}

Quantity::~Quantity() {

}



PriceLevel::PriceLevel(uint32_t price) :
		_price(price) {
}

void PriceLevel::addQuantity(uint32_t quantity, uint32_t user, uint32_t userOrder) {
	Quantity quantityEntry(quantity, user, userOrder);
	_quantitiesInTimeOrder.emplace_back(quantityEntry);
}


PriceLevel::~PriceLevel() {

}

OrderBook::OrderBook() {

}

void OrderBook::addOrder(bool isBuy, uint32_t price, uint32_t quantity, uint32_t user, uint32_t userOrder ) {

	ORDERS_TYPE & orders = _sellOrders;
	if( isBuy ) {
		orders = _buyOrders;
	}

	// See if PriceLevel already exists
	auto it = orders.find(price);
	if (it != orders.end()) {
		// PriceLevel already exists, add new quantity.
		it->second.addQuantity(quantity, user, userOrder);
	} else {
		// PriceLevel doesn't already exist, create it and emplace.
		PriceLevel priceLevel(price);
		priceLevel.addQuantity(quantity, user, userOrder);
		orders.emplace(price, priceLevel);
	}


}


OrderBook::~OrderBook() {
}

