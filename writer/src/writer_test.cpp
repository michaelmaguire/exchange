#include <gtest/gtest.h>
#include "protowriter.h"
#include "order.pb.h"


TEST(ProtobufWriterSuite, sendNewOrder) {

	ProtoWriter protowriter(1234);

	exchange::ExchangeMessage exchangeMessage;
	auto newOrder = new exchange::NewOrder();
	newOrder->set_user(1);
	newOrder->set_symbol("IBM");
	newOrder->set_price(10);
	newOrder->set_quantity(100);
	newOrder->set_side(exchange::NewOrder_SideType::NewOrder_SideType_BUY);
	newOrder->set_userorder(1);
	exchangeMessage.set_allocated_neworder(newOrder);

	protowriter.send(exchangeMessage);
}
