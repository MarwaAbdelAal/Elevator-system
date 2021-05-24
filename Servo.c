#include "Main.h"
#include "Port.h"
#include "Servo.h"

void SERVO_Init()
{
    GPIO_InitPortPin(SERVO_PORT_dir, SERVO_PIN, GPIO_OUT);
}