#include "writer.h"
#include <gtest/gtest.h>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "order.pb.h"


TEST(ProtobufWriterSuite, sendNewOrder) {

	Writer writer;
	writer.setup(1234);

	exchange::ExchangeMessage exchangeMessage;
	auto newOrder = new exchange::NewOrder();
	newOrder->set_user(1);
	newOrder->set_symbol("IBM");
	newOrder->set_price(10);
	newOrder->set_quantity(100);
	newOrder->set_side(exchange::NewOrder_SideType::NewOrder_SideType_BUY);
	newOrder->set_userorder(1);
	exchangeMessage.set_allocated_neworder(newOrder);

    boost::asio::streambuf streamBuffer;
    std::ostream outputStream(&streamBuffer);

    // Scoped to ensure CodedOutputStream is flushed.
    {
      ::google::protobuf::io::OstreamOutputStream rawOutputStream(&outputStream);
      ::google::protobuf::io::CodedOutputStream codedOutputStream(&rawOutputStream);
      codedOutputStream.WriteVarint32(exchangeMessage.ByteSize());
      exchangeMessage.SerializeToCodedStream(&codedOutputStream);
    }

	writer.send(streamBuffer);
}
