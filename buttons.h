#ifndef __BUTTON_H__
#define __BUTTON_H__




void button_init(unsigned char portNumber, unsigned char pinNumber);

unsigned char button_read(unsigned char portNumber, unsigned char pinNumber);



#endif // __BUTTON_H__