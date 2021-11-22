/*
 * Copyright: 2021, Michael Maguire
 */

#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "proto_writer.h"

using namespace boost::log::trivial;

ProtoWriter::ProtoWriter(unsigned short port) :
		Writer(port) {

}

ProtoWriter::~ProtoWriter() {
}

void ProtoWriter::send(const google::protobuf::Message &message) {

	boost::asio::streambuf streamBuffer;
	std::ostream outputStream(&streamBuffer);

	// Scoped to ensure CodedOutputStream is flushed.
	{
		::google::protobuf::io::OstreamOutputStream rawOutputStream(
				&outputStream);
		::google::protobuf::io::CodedOutputStream codedOutputStream(
				&rawOutputStream);

		const ::google::protobuf::uint32 PACKET_MAGIC = 6664; // rudimentary packet identification
		const ::google::protobuf::uint32 PACKET_VERSION = 1; // room to grow
		codedOutputStream.WriteLittleEndian32(PACKET_MAGIC);
		codedOutputStream.WriteLittleEndian32(PACKET_VERSION);
		codedOutputStream.WriteVarint32(message.ByteSize());

		BOOST_LOG_SEV(_lg, info)
		<< "ProtoWriter::send message[" << message.DebugString() << "]";

		message.SerializeToCodedStream(&codedOutputStream);
	}

	Writer::send(streamBuffer);
}
