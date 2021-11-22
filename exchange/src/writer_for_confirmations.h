/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef WRITER_FOR_CONFIRMATIONS_H_
#define WRITER_FOR_CONFIRMATIONS_H_

#include "proto_writer.h"
#include "confirmations_callback.h"

class WriterForConfirmations: public ConfirmationsCallback, private ProtoWriter {
public:
	WriterForConfirmations(unsigned short port);
	virtual ~WriterForConfirmations();

	virtual void sendOrderAcknowledgement(uint32_t user, uint32_t userOrder);

	virtual void sendTradeConfirmation(uint32_t useridbuy,
			uint32_t userorderidbuy, uint32_t useridsell,
			uint32_t userorderidsell, uint32_t price, uint32_t quantity,
			std::string symbol);

	virtual void sendTopOfBookChange(bool buy, uint32_t price,
			uint32_t quantity, bool sideElimination);

};

#endif /* WRITER_FOR_CONFIRMATIONS_H_ */
