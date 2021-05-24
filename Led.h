#ifndef __LED_H__
#define __LED_H__

#define LED_DELAY_MS (1000)

typedef enum
{
    LED_1,
    LED_2,
}tLED;

typedef enum
{
   LED_OFF,
   LED_ON
}tLED_State;


void LED_Init(tLED led, tLED_State state);
void LED_SetState(tLED led, tLED_State state);
tLED_State LED_GetState(tLED led);
void LED_Toggle(tLED led);

#endif // __LED_H__
