/*
 * Copyright: 2021, Michael Maguire
 */

#include "order_book.h"

#include <algorithm>

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

bool PriceLevel::cancelOrder(uint32_t user, uint32_t userOrder) {
	bool found = false;
	for (auto it = _quantitiesInTimeOrder.begin();
			it != _quantitiesInTimeOrder.end(); ++it) {

		if ((it->_user == user) && (it->_userOrder == userOrder)) {
			_quantitiesInTimeOrder.erase(it);
			found = true;
			break;
		}
	}

	return found;
}

bool PriceLevel::exhaust(ConfirmationsCallback *confirmationsCallback,
		const std::string &symbol, uint32_t &quantityRemaining,
		const Order &order) {

	bool tradeTookPlace = false;

	for (auto it = _quantitiesInTimeOrder.begin();
			((quantityRemaining > 0) && (it != _quantitiesInTimeOrder.end()));
			/* no ++it to handled erase */) {

		//std::cout << "PriceLevel::exhaust\n";

		// If we made it into this look, then some trading will happen.
		tradeTookPlace = true;

		auto quantity = *it;

		uint32_t maximumWeCanExercise = std::min(quantityRemaining,
				quantity._quantity);

		quantity._quantity -= maximumWeCanExercise;
		quantityRemaining -= maximumWeCanExercise;

		if (order._side == Order::BUY) {
			confirmationsCallback->sendTradeConfirmation(order._user,
					order._userOrder, quantity._user, quantity._userOrder,
					_price, maximumWeCanExercise, symbol);
		} else {
			confirmationsCallback->sendTradeConfirmation(quantity._user,
					quantity._userOrder, order._user, order._userOrder, _price,
					maximumWeCanExercise, symbol);
		}

		// If we've just exhausted a quantity, then erase.
		if (quantity._quantity == 0) {
			it = _quantitiesInTimeOrder.erase(it);
		} else {
			++it;
		}

	}

	return tradeTookPlace;
}

Quantity& PriceLevel::front() {
	return _quantitiesInTimeOrder.front();
}

Quantity& PriceLevel::back() {
	return _quantitiesInTimeOrder.back();
}

OrderBook::OrderBook(ConfirmationsCallback *confirmationsCallback,
		const std::string &symbol) :
		_confirmationsCallback(confirmationsCallback), _symbol(symbol) {
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

	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::addOrder before add [" << *this << "]";

	ORDERS_TYPE *orders = &_sellOrders;
	ORDERS_TYPE *oppositeOrders = &_buyOrders;
	if (Order::Side::BUY == order._side) {
		orders = &_buyOrders;
		oppositeOrders = &_sellOrders;
	}

	// Perform order validation
	if (order._quantity == 0) {
		BOOST_LOG_SEV(_lg, error)
		<< "OrderBook::addOrder invalid order quantity";
		return;
	}

	_confirmationsCallback->sendOrderAcknowledgement(order._user,
			order._userOrder);

	bool tradeTookPlace = false;
	bool addedToBook = false;

	uint32_t price = order._price;
	uint32_t quantityRemaining = order._quantity;
	bool buy = (Order::Side::BUY == order._side);

	// Check if market order.
	if (price == 0) {
		// Market order.
		while (quantityRemaining > 0 && oppositeOrders->size() > 0) {

			//std::cout << "market while (quantityRemaining\n";

			auto priceLevel =
					(buy ? oppositeOrders->begin()->second : oppositeOrders->rbegin()->second);
			tradeTookPlace = tradeTookPlace
					| priceLevel.exhaust(_confirmationsCallback, _symbol,
							quantityRemaining, order);
		}
	} else {

		// Limit order.

		// See if we can match immediately.
		bool oppositeSideHasAttractivePrice = true;
		while ((quantityRemaining > 0) && (oppositeOrders->size()) > 0
				&& oppositeSideHasAttractivePrice) {

			//std::cout << "limit while (quantityRemaining[" << quantityRemaining <<"] oppositeOrders->size()[" << oppositeOrders->size() << "]\n";

			// Be careful that if you are BUY, then oppositeOrders are SELL, so begin() gives top of the book.
			// Otherwise if you are SELL, the oppositeOrders are BUY, so rbegin() gives top of the book.
			auto priceLevel =
					(buy ? oppositeOrders->begin()->second : oppositeOrders->rbegin()->second);

			// See if the price is right: if I'm buying and I'm willing to pay more than you wanted,
			// of if I'm selling and you're willing to pay more than I asked for.
			if ((buy && (price >= priceLevel._price))
					|| (!buy && (price <= priceLevel._price))) {
				tradeTookPlace = tradeTookPlace
						| priceLevel.exhaust(_confirmationsCallback, _symbol,
								quantityRemaining, order);
			} else {
				oppositeSideHasAttractivePrice = false;
			}
		}

		// If there's anything left of the limit order, place what's left on the book.
		if (quantityRemaining > 0) {

			// See if PriceLevel already exists
			auto it = orders->find(price);
			if (it != orders->end()) {
				BOOST_LOG_SEV(_lg, trace)
				<< "OrderBook::addOrder PriceLevel price[" << price
						<< "] already exists, add new order[" << order << "]";
				it->second.addQuantity(quantityRemaining, order._user,
						order._userOrder);
			} else {
				BOOST_LOG_SEV(_lg, trace)
				<< "OrderBook::addOrder PriceLevel price[" << price
						<< "] doesn't already exists, creating with new order["
						<< order << "]";
				PriceLevel priceLevel(price);
				priceLevel.addQuantity(quantityRemaining, order._user,
						order._userOrder);
				orders->emplace(price, priceLevel);
			}

			addedToBook = true;
		}
	}

	if (tradeTookPlace || addedToBook) {

		if (buy) {
			// BUY, so top of book is greatest price, use rbegin().
			PriceLevel topOfBookPriceLevel = orders->rbegin()->second;
			uint32_t topOfBookPrice = topOfBookPriceLevel._price;
			_confirmationsCallback->sendTopOfBookChange(buy, topOfBookPrice,
					order._quantity,
					(oppositeOrders->size() == 0) && tradeTookPlace);
		} else {
			// SELL, so top of book is least price, use begin().
			PriceLevel topOfBookPriceLevel = orders->begin()->second;
			uint32_t topOfBookPrice = topOfBookPriceLevel._price;
			_confirmationsCallback->sendTopOfBookChange(buy, topOfBookPrice,
					order._quantity,
					(oppositeOrders->size() == 0) && tradeTookPlace);
		}
	}

	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::addOrder after add [" << *this << "]";

}

bool OrderBook::cancelOrder(uint32_t user, uint32_t userOrder) {
	bool found = false;

	for (auto it = _buyOrders.begin(); it != _buyOrders.end(); ++it) {
		found = it->second.cancelOrder(user, userOrder);
		if (found) {
			break;
		}
	}
	if (!found) {
		for (auto it = _sellOrders.begin(); it != _sellOrders.end(); ++it) {
			found = it->second.cancelOrder(user, userOrder);
			if (found) {
				break;
			}
		}
	}

	if (found) {
		_confirmationsCallback->sendOrderAcknowledgement(user, userOrder);

		// TODO: an order cancellation could change the top of the book.
		// Not sure whether our log output spec is capable of communicating that, though.
		//_confirmationsCallback->sendTopOfBookChange(
		//		Order::Side::BUY == order._side, price,
		//		order._quantity - quantityRemaining,
		//		oppositeOrders->size() == 0);

	}

	return found;
}

void OrderBook::flush() {
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::flush before flush [" << *this << "]";

	_buyOrders.clear();
	_sellOrders.clear();

	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::flush after flush [" << *this << "]";
}

// Returns the top of the order book, first BUY, second SELL.
const std::pair<Order, Order> OrderBook::top() const {

	if (0 == _buyOrders.size()) {
		throw std::out_of_range("No buy orders yet");
	}
	if (0 == _sellOrders.size()) {
		throw std::out_of_range("No sell orders yet");
	}

// Take advantage of  map's ordering guarantee, given that price is our key.
	auto topByePriceLevel = _buyOrders.begin()->second;
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::top topByePriceLevel[" << topByePriceLevel << "]";

	auto topSellPriceLevel = _sellOrders.rbegin()->second;
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::top topSellPriceLevel[" << topSellPriceLevel << "]";

	auto topBuyFirstInTimeQuantity = topByePriceLevel.front();
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::top topBuyFirstInTimeQuantity[" << topBuyFirstInTimeQuantity
			<< "]";
	auto topSellFirstInTimeQuantity = topSellPriceLevel.front();
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::top topSellFirstInTimeQuantity["
			<< topSellFirstInTimeQuantity << "]";

	Order topBye(Order::BUY, topByePriceLevel._price,
			topBuyFirstInTimeQuantity);
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::top topBye[" << topBye << "]";
	Order topSell(Order::SELL, topSellPriceLevel._price,
			topSellFirstInTimeQuantity);
	BOOST_LOG_SEV(_lg, trace)
	<< "OrderBook::top topSell[" << topSell << "]";

	return std::make_pair(topBye, topSell);

}

