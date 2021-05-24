#ifndef __MAIN_H__
#define __MAIN_H__

#include "C8051F020.h"

/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0 (0)
#define GPIO_PIN_1 (1)
#define GPIO_PIN_2 (2)
#define GPIO_PIN_3 (3)
#define GPIO_PIN_4 (4)
#define GPIO_PIN_5 (5)
#define GPIO_PIN_6 (6)
#define GPIO_PIN_7 (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORT0_DATA (P0)
#define GPIO_PORT0_DIRECTION (P0MDOUT)

#define GPIO_PORT1_DATA (P1)
#define GPIO_PORT1_DIRECTION (P1MDOUT)

#define GPIO_PORT2_DATA (P2)
#define GPIO_PORT2_DIRECTION (P2MDOUT)

#define GPIO_PORT3_DATA (P3)
#define GPIO_PORT3_DIRECTION (P3MDOUT)

#define GPIO_PORT4_DATA (P4)
#define GPIO_PORT4_DIRECTION (P74OUT)

#define GPIO_PORT5_DATA (P5)
#define GPIO_PORT5_DIRECTION (P74OUT)

/* GPIO direction setting */
#define GPIO_OUT (1)
#define GPIO_IN (0)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION) ((CONTROL) = ((DIRECTION) ? (~GPIO_OUT) : (GPIO_OUT)))
#define GPIO_WritePort(PORT, DATA) ((PORT) = (DATA))
#define GPIO_ReadPort(PORT) (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION) ((CONTROL) = (CONTROL & (~(1 << PIN))) | (DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA) ((PORT) = (PORT & (~(1 << PIN))) | (DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN) (((PORT) & (1 << PIN)) >> (PIN))
/* End of code filling */

/* Standard data types */
typedef unsigned int tWord;

#endif // __MAIN_H__
