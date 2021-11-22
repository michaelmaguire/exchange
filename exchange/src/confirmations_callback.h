/*
 * Copyright: 2021, Michael Maguire
 */

#ifndef CONFIRMATIONS_CALLBACK_H_
#define CONFIRMATIONS_CALLBACK_H_

#include <cstdint>
#include <string>

class ConfirmationsCallback {
public:
	ConfirmationsCallback();
	virtual ~ConfirmationsCallback() {}

	virtual void sendOrderAcknowledgement(uint32_t user,
			uint32_t userOrder) = 0;

	virtual void sendTradeConfirmation(uint32_t useridbuy,
			uint32_t userorderidbuy, uint32_t useridsell,
			uint32_t userorderidsell, uint32_t price, uint32_t quantity,
			std::string symbol) = 0;

	virtual void sendTopOfBookChange(bool buy, uint32_t price,
			uint32_t quantity, bool sideElimination) = 0;

};

#endif /* CONFIRMATIONS_CALLBACK_H_ */
