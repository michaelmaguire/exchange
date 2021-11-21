/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef PROTO_WRITER_H_
#define PROTO_WRITER_H_

#include "writer.h"
#include "order.pb.h"

class ProtoWriter: public Writer {
public:
	explicit ProtoWriter(unsigned short port);
	~ProtoWriter();
	void send(const google::protobuf::Message & message);
};

#endif /* PROTO_WRITER_H_ */
