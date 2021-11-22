/*
 * Copyright: 2021, Michael Maguire
 */

#include "writer_for_confirmations.h"

#include "order.pb.h"

using namespace boost::log::trivial;

extern uint64_t g_sequenceNumber;

WriterForConfirmations::WriterForConfirmations(unsigned short port) :
		ProtoWriter(port) {

}

WriterForConfirmations::~WriterForConfirmations() {
}

void WriterForConfirmations::sendOrderAcknowledgement(uint32_t user,
		uint32_t userOrder) {

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(g_sequenceNumber++);
	auto orderAcknowledgement = new exchange::OrderAcknowledgement();
	orderAcknowledgement->set_user(user);
	orderAcknowledgement->set_userorder(userOrder);

	exchangeMessage.set_allocated_orderacknowledgement(orderAcknowledgement);
	send(exchangeMessage);
}

void WriterForConfirmations::sendTradeConfirmation(uint32_t useridbuy,
		uint32_t userorderidbuy, uint32_t useridsell, uint32_t userorderidsell,
		uint32_t price, uint32_t quantity, std::string symbol) {

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(g_sequenceNumber++);
	auto tradeConfirmation = new exchange::TradeConfirmation();
	tradeConfirmation->set_useridbuy(useridbuy);
	tradeConfirmation->set_userorderidbuy(userorderidbuy);
	tradeConfirmation->set_useridsell(useridsell);
	tradeConfirmation->set_userorderidsell(userorderidsell);
	tradeConfirmation->set_price(price);
	tradeConfirmation->set_quantity(quantity);
	tradeConfirmation->set_symbol(symbol);

	exchangeMessage.set_allocated_tradeconfirmation(tradeConfirmation);
	send(exchangeMessage);
}

void WriterForConfirmations::sendTopOfBookChange(bool buy, uint32_t price,
		uint32_t quantity, bool sideElimination) {

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(g_sequenceNumber++);
	auto topOfBookChange = new exchange::TopOfBookChange();
	topOfBookChange->set_side(
			buy ? topOfBookChange->BUY : topOfBookChange->SELL);
	topOfBookChange->set_price(price);
	topOfBookChange->set_quantity(quantity);
	topOfBookChange->set_sideelimination(sideElimination);
	topOfBookChange->set_symbol("IBM");

	exchangeMessage.set_allocated_topofbookchange(topOfBookChange);
	send(exchangeMessage);
}

