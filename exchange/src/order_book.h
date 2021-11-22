/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef ORDER_BOOK_H_
#define ORDER_BOOK_H_

#include <cstdint>
#include <iostream>
#include <vector>
#include <map>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include "writer_for_confirmations.h"

// We use Quantity as an abstraction for an entry in our PriceLevel.
class Quantity {
public:
	explicit Quantity(uint32_t quantity, uint32_t user, uint32_t userOrder);
	virtual ~Quantity();
	friend std::ostream& operator<<(std::ostream &os, const Quantity &q);

	// I've chosen not to use accessors for these at this level.
	uint32_t _quantity;

	uint32_t _user;			// required for cancellation and trade confirmation
	uint32_t _userOrder;	// required for cancellation and trade confirmation

};

// We don't use Order for our internal storage, but we do use it for input and output.
class Order {
public:
	enum Side {
		BUY = 0, SELL = 1
	};

	Order(Side side, uint32_t price, uint32_t quantity, uint32_t user,
			uint32_t userOrder);
	Order(Side side, uint32_t price, const Quantity &quantity);
	virtual ~Order();
	friend std::ostream& operator<<(std::ostream &os, const Order &q);

// I've chosen not to use accessors for these at this level.
	Side _side;

	uint32_t _price;
	uint32_t _quantity;

	uint32_t _user;			// required for cancellation and trade confirmation
	uint32_t _userOrder;	// required for cancellation and trade confirmation

};

std::ostream& operator<<(std::ostream &os, const Order::Side &s);

// We use PriceLevel to store orders at a given price.
class PriceLevel {
public:
	explicit PriceLevel(uint32_t price);
	virtual ~PriceLevel();
	friend std::ostream& operator<<(std::ostream &os, const PriceLevel &pl);

	void addQuantity(uint32_t quantity, uint32_t user, uint32_t userOrder);

	// Returns true if the order to cancel was found.
	bool cancelOrder(uint32_t user, uint32_t userOrder);

	// Returns true if any trading took place.
	bool exhaust(ConfirmationsCallback *confirmationsCallback,
			const std::string &symbol, uint32_t quantityRemaining,
			const Order &order);

	// I've chosen not to use an accessor for this at this level.
	uint32_t _price;

	Quantity& front();
	Quantity& back();

private:

	std::vector<Quantity> _quantitiesInTimeOrder;
};

// Our currently implementation of an OrderBook is two ordered maps, one for each of buy and sell sides.
// Each map associates a given price to a PriceLevel structure that tracks Quantities for individual orders.
// We accept the Orders structure for adding new orders as well as returning information about top of the book.
class OrderBook {
public:
	OrderBook(ConfirmationsCallback *confirmationsCallback,
			const std::string &symbol);
	virtual ~OrderBook();
	friend std::ostream& operator<<(std::ostream &os, const OrderBook &ob);

	void addOrder(const Order &order);
	bool cancelOrder(uint32_t user, uint32_t userOrder);
	void flush();

	// Returns the top of the order book, first BYE, second SELL.
	const std::pair<Order, Order> top() const;

	// Reconcile the book to see if a trade can be performed.
	void cross();

private:
	ConfirmationsCallback *_confirmationsCallback;
	std::string _symbol; // only for debugging logs

	typedef std::map<uint32_t, PriceLevel> ORDERS_TYPE;

	ORDERS_TYPE _buyOrders;
	ORDERS_TYPE _sellOrders;

	mutable boost::log::sources::severity_logger<
			boost::log::trivial::severity_level> _lg;

};

#endif /* ORDER_BOOK_H_ */
