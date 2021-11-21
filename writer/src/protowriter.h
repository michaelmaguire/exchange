#include "writer.h"
#include "order.pb.h"

class ProtoWriter: public Writer {
public:
	explicit ProtoWriter(unsigned short port);
	~ProtoWriter();
	void send(const google::protobuf::Message & message);
};
