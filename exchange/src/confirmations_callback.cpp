/*
 * Copyright: 2021, Michael Maguire
 */

#include "confirmations_callback.h"

ConfirmationsCallback::ConfirmationsCallback() {

}

ConfirmationsCallback::~ConfirmationsCallback() {
}

void ConfirmationsCallback::sendOrderAcknowledgement(uint32_t user,
		uint32_t userOrder) {

}

void ConfirmationsCallback::sendTradeConfirmation(uint32_t useridbuy,
		uint32_t userorderidbuy, uint32_t useridsell, uint32_t userorderidsell,
		uint32_t price, uint32_t quantity, std::string symbol) {

}

void ConfirmationsCallback::sendTopOfBookChange(bool buy, uint32_t price,
		uint32_t quantity, bool sideElimination) {

}

