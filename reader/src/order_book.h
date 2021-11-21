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

class PriceLevel {
public:
	explicit PriceLevel(uint32_t price);
	virtual ~PriceLevel();
	friend std::ostream& operator<<(std::ostream &os, const PriceLevel &pl);

	void addQuantity(uint32_t quantity, uint32_t user, uint32_t userOrder);

	// I've chosen not to use an accessor for this at this level.
	uint32_t _price;

private:

	std::vector<Quantity> _quantitiesInTimeOrder;
};

class OrderBook {
public:
	OrderBook();
	virtual ~OrderBook();
	friend std::ostream& operator<<(std::ostream &os, const OrderBook &ob);

	void addOrder(bool isBuy, uint32_t price, uint32_t quantity, uint32_t user,
			uint32_t userOrder);

private:

	typedef std::map<uint32_t, PriceLevel> ORDERS_TYPE;

	ORDERS_TYPE _buyOrders;
	ORDERS_TYPE _sellOrders;


	boost::log::sources::severity_logger<boost::log::trivial::severity_level> _lg;

};

#endif /* ORDER_BOOK_H_ */
