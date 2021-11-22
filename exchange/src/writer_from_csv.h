/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef WRITER_FROM_CSV_H_
#define WRITER_FROM_CSV_H_

#include "proto_writer.h"
#include <vector>

class WriterFromCSV: public ProtoWriter {
public:
	WriterFromCSV(unsigned short port);
	virtual void loadAndWriteFile(const std::string &filename);
	virtual ~WriterFromCSV();
protected:
	virtual void processLineTokens(const std::vector<std::string> &tokens);

};

#endif /* WRITER_FROM_CSV_H_ */
