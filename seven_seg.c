#include "Main.h"
#include "Port.h"
#include "seven_seg.h"

unsigned char numbers[5]={ 0x3f,0x06,0x5b,0x4f,0x66};

void sevenSegment_init(unsigned char portNumber)
{ 
    // initializing port 1 (7 segment) output
    GPIO_InitPort(portNumber, 1); 
}

void sevenSegment_write(unsigned char floorIndex)
{
    GPIO_WritePort(SevenSeg_PORT, numbers[floorIndex]);
    
}
