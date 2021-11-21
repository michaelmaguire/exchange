#include "protowriter.h"

#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"


ProtoWriter::ProtoWriter(unsigned short port) : Writer(port) {

}

ProtoWriter::~ProtoWriter() {
}

void ProtoWriter::send(const google::protobuf::Message & message) {

	boost::asio::streambuf streamBuffer;
    std::ostream outputStream(&streamBuffer);

    // Scoped to ensure CodedOutputStream is flushed.
    {
      ::google::protobuf::io::OstreamOutputStream rawOutputStream(&outputStream);
      ::google::protobuf::io::CodedOutputStream codedOutputStream(&rawOutputStream);
      codedOutputStream.WriteVarint32(message.ByteSize());
      message.SerializeToCodedStream(&codedOutputStream);
    }

	Writer::send(streamBuffer);
}
