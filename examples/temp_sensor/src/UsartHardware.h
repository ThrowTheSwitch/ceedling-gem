#ifndef _USARTHARDWARE_H
#define _USARTHARDWARE_H

#include "Types.h"

void UsartHardware_Init(uint8 baudRateRegisterSetting);
void UsartHardware_TransmitString(char* data);
void UsartHardware_ReceiveString(char* data, uint16 maxLen);

#endif // _USARTHARDWARE_H
