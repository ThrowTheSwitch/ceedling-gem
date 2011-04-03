#include "unity.h"
#include "Types.h"
#include "UsartHardware.h"
#include "AT91SAM7X256.h"
#include "MockUsartConfigurator.h"
#include "MockUsartPutChar.h"
#include "MockUsartGetChar.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void testInitShouldConfigureUsartPeripheralByCallingConfiguratorAppropriately(void)
{
  Usart_ConfigureUsartIO_Expect();
  Usart_EnablePeripheralClock_Expect();
  Usart_Reset_Expect();
  Usart_ConfigureMode_Expect();
  Usart_SetBaudRateRegister_Expect(73);
  Usart_Enable_Expect();

  UsartHardware_Init(73);
}

void testTransmitStringShouldSendDesiredStringOutUsingUsart(void)
{
  Usart_PutChar_Expect('h');
  Usart_PutChar_Expect('e');
  Usart_PutChar_Expect('l');
  Usart_PutChar_Expect('l');
  Usart_PutChar_Expect('o');
  
  UsartHardware_TransmitString("hello");
}

void testUsartHardwareReceiveStringShouldReceiveUntilNullTerminatorIsReached(void) //reqs: 
{
    char message[16] = "";

    UsartHardware_GetChar_ExpectAndReturn('W');
    UsartHardware_GetChar_ExpectAndReturn('a');
    UsartHardware_GetChar_ExpectAndReturn('s');
    UsartHardware_GetChar_ExpectAndReturn('s');
    UsartHardware_GetChar_ExpectAndReturn('u');
    UsartHardware_GetChar_ExpectAndReturn('p');
    UsartHardware_GetChar_ExpectAndReturn('!');
    UsartHardware_GetChar_ExpectAndReturn(NULL);

    UsartHardware_ReceiveString(message, sizeof(message));

    TEST_ASSERT_EQUAL_STRING("Wassup!", message);
}
