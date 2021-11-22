/*
 * Copyright: 2021, Michael Maguire
 */

#include <gtest/gtest.h>
#include "order.pb.h"
#include "proto_writer.h"

const unsigned short _exchange_multicast_udp_port = 1234;

TEST(ProtobufWriterSuite, sendNewOrders) {

	ProtoWriter protowriter(_exchange_multicast_udp_port);

	uint64_t sequenceNumber = 0;

	for (uint32_t order = 0; order < 2; ++order) {
		exchange::ExchangeMessage exchangeMessage;
		exchangeMessage.set_sequencenumber(sequenceNumber++);
		auto newOrder = new exchange::NewOrder();
		newOrder->set_user(1);
		newOrder->set_symbol("IBM");
		newOrder->set_price(10);
		newOrder->set_quantity(100);
		newOrder->set_side(exchange::NewOrder_SideType::NewOrder_SideType_BUY);
		newOrder->set_userorder(order);
		exchangeMessage.set_allocated_neworder(newOrder);
		protowriter.send(exchangeMessage);
	}

	for (uint32_t order = 0; order < 2; ++order) {
		exchange::ExchangeMessage exchangeMessage;
		exchangeMessage.set_sequencenumber(sequenceNumber++);
		auto newOrder = new exchange::NewOrder();
		newOrder->set_user(1);
		newOrder->set_symbol("IBM");
		newOrder->set_price(11);
		newOrder->set_quantity(100);
		newOrder->set_side(exchange::NewOrder_SideType::NewOrder_SideType_SELL);
		newOrder->set_userorder(order);
		exchangeMessage.set_allocated_neworder(newOrder);
		protowriter.send(exchangeMessage);
	}

}

TEST(ProtobufWriterSuite, sendFlushOrder) {

	ProtoWriter protowriter(_exchange_multicast_udp_port);

	uint64_t sequenceNumber = 0;

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(sequenceNumber++);
	auto flushOrder = new exchange::FlushOrder();
	exchangeMessage.set_allocated_flushorder(flushOrder);
	protowriter.send(exchangeMessage);
}

TEST(ProtobufWriterSuite, sendOrderAcknowledgement) {

	ProtoWriter protowriter(_exchange_multicast_udp_port);

	uint64_t sequenceNumber = 0;

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(sequenceNumber++);
	auto orderAcknowledgement = new exchange::OrderAcknowledgement();
	orderAcknowledgement->set_user(1);
	orderAcknowledgement->set_userorder(2);

	exchangeMessage.set_allocated_orderacknowledgement(orderAcknowledgement);
	protowriter.send(exchangeMessage);
}

TEST(ProtobufWriterSuite, sendTradeConfirmation) {

	ProtoWriter protowriter(_exchange_multicast_udp_port);

	uint64_t sequenceNumber = 0;

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(sequenceNumber++);
	auto tradeConfirmation = new exchange::TradeConfirmation();
	tradeConfirmation->set_useridbuy(1);
	tradeConfirmation->set_userorderidbuy(2);
	tradeConfirmation->set_useridsell(2);
	tradeConfirmation->set_userorderidsell(3);
	tradeConfirmation->set_price(10);
	tradeConfirmation->set_quantity(100);
	tradeConfirmation->set_symbol("IBM");

	exchangeMessage.set_allocated_tradeconfirmation(tradeConfirmation);
	protowriter.send(exchangeMessage);
}

TEST(ProtobufWriterSuite, sendTopOfBookChange) {

	ProtoWriter protowriter(_exchange_multicast_udp_port);

	uint64_t sequenceNumber = 0;

	exchange::ExchangeMessage exchangeMessage;
	exchangeMessage.set_sequencenumber(sequenceNumber++);
	auto topOfBookChange = new exchange::TopOfBookChange();
	topOfBookChange->set_side(topOfBookChange->BUY);
	topOfBookChange->set_price(10);
	topOfBookChange->set_quantity(100);
	topOfBookChange->set_sideelimination(true);
	topOfBookChange->set_symbol("IBM");

	exchangeMessage.set_allocated_topofbookchange(topOfBookChange);
	protowriter.send(exchangeMessage);
}

