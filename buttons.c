#include "Main.h"
#include "Port.h"
#include "buttons.h"

void button_init(unsigned char portNumber, unsigned char pinNumber)
{
    GPIO_InitPortPin(portNumber, pinNumber, 0);
}

unsigned char button_read(unsigned char portNumber, unsigned char pinNumber)
{
    unsigned char x;
    x = GPIO_ReadPortPin(portNumber, pinNumber);
    return x;
}
