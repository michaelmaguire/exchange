/*
 * Copyright: 2021, Michael Maguire
 */

#include <gtest/gtest.h>
#include "order.pb.h"
#include "proto_writer.h"

const unsigned short EXCHANGE_MESSAGE_UDP_MULTICAST_PORT = 1234;

TEST(ProtobufWriterSuite, sendNewOrder) {

	ProtoWriter protowriter(EXCHANGE_MESSAGE_UDP_MULTICAST_PORT);

	uint64_t sequenceNumber = 0;

	for (uint32_t order = 0; order < 100; ++order) {
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
}
