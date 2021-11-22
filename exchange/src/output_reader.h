/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef OUTPUT_READER_H_
#define OUTPUT_READER_H_

#include "proto_reader.h"
#include "order_book.h"

class OutputReader: public ProtoReader {
public:
	OutputReader();
	virtual ~OutputReader();

protected:

	virtual void do_read(const exchange::ExchangeMessage &exchangeMessage);

};

#endif /* OUTPUT_READER_H_ */
