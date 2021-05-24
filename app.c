#include "Main.h"
#include "Port.h"
#include "Led.h"
#include "buttons.h"
#include "seven_seg.h"
#include "Servo.h"
#include <stdio.h>

#define PWM_Period 0xB7FE
sbit Servo_Motor_Pin = P3^2;
float cycle[5] ={2.7 , 6.4 , 7.5 , 8.6 , 9.7} ;
unsigned int ON_Period, OFF_Period, DutyCycle;

unsigned char floors[5]={ 0,0,0,0,0};
unsigned char up[5]={ 0,0,0,0,0};
unsigned char down[5]={ 0,0,0,0,0};
unsigned char up_sum = 0;
unsigned char down_sum = 0;
unsigned char selectedFloor = 0;
unsigned char currentFloor = 0;
unsigned char Direction = 1; // 0= down , 1= up
unsigned char moving = 0 ;
unsigned char check_door = 0; // 0= door closed , 1= door opened
void elevatorUp();
void elevatorDown();
void getDirection();
void setDirection(unsigned char x);
void moveElevator();
void pullDown(unsigned char requestFloor);
void pullUp(unsigned char requestFloor);
unsigned char final_floor_up();
unsigned char final_floor_down();
void open_door();
void Set_DutyCycle_To(float duty_cycle);

void Delay_MS(unsigned int ms)
{
    unsigned int i;
    unsigned int j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++)
        {
        }
    }
}
void Timer_init()
{
    TMOD = 0x11;
    TH0 = (PWM_Period >> 8);/* 20ms timer value */
	TL0 = PWM_Period;
    TR0 = 1;
    TL1 = 0x00;
    TH1 = 0x00;
    TR1 = 1;
}
// (void) interrupt 1
void Check_buttons(void) interrupt 3

{

        unsigned char i = 0;


        if (!button_read(BUTTONg_PORT, BUTTON_G_PIN))
        {   
            floors[0] = 1;
            selectedFloor = 0;
            getDirection();
        }
        if (!button_read(BUTTON1_PORT, BUTTON_1_PIN))
        {
            floors[1] = 1;
            selectedFloor = 1;
            getDirection();
        }
        if (!button_read(BUTTON2_PORT, BUTTON_2_PIN))
        {
            floors[2] = 1;
            selectedFloor = 2;
            getDirection();
        }
        if (!button_read(BUTTON3_PORT, BUTTON_3_PIN))
        {   
            floors[3] = 1;
            selectedFloor = 3;
            getDirection();
        }
        if (!button_read(BUTTON4_PORT, BUTTON_4_PIN))
        {   
            floors[4] = 1;
            selectedFloor = 4;
            getDirection();
        }

        if (!button_read(BUTTON_Gup_PORT, BUTTON_GUP_PIN)) //G up
        {
            down[0] = 1;
            selectedFloor = 0;
            setDirection(0);
        }

        if (!button_read(BUTTON_1up_PORT, BUTTON_1UP_PIN)) // 1up
        {

            up[1] = 1;
            selectedFloor = 1;
            setDirection(1);
        }
        if (!button_read(BUTTON_2up_PORT, BUTTON_2UP_PIN)) // 2up
        {

            up[2] = 1;
            selectedFloor = 2;
            setDirection(1);
        }
        if (!button_read(BUTTON_3up_PORT, BUTTON_3UP_PIN)) // 3up
        {

            up[3] = 1;
            selectedFloor = 3;
            setDirection(1);
        }

        if (!button_read(BUTTON_1down_PORT, BUTTON_1DOWN_PIN)) // 1down
        {

            down[1] = 1;
            selectedFloor = 1;
            setDirection(0);
        }

        if (!button_read(BUTTON_2down_PORT, BUTTON_2DOWN_PIN)) // 2down
        {
            down[2] = 1;
            selectedFloor = 2;
            setDirection(0);
        }

        if (!button_read(BUTTON_3down_PORT, BUTTON_3DOWN_PIN)) // 3down
        {
            down[3] = 1;
            selectedFloor = 3;
            setDirection(0);
        }

        if (!button_read(BUTTON_4down_PORT, BUTTON_4DOWN_PIN)) // 4down
        {
            up[4] = 1;
            selectedFloor = 4;
            setDirection(1);
        }
up_sum = 0;
down_sum =0;
for (i ; i <= 4; i++)
    {
        up_sum = up_sum + up[i];
        down_sum = down_sum + down[i];
    }        

    
}

void Timer0_ISR(void) interrupt 1	
{
	Servo_Motor_Pin = !Servo_Motor_Pin;
	if(Servo_Motor_Pin)
	{
		TH0 = (ON_Period >> 8);
		TL0 = ON_Period;
	}	
	else
	{
		TH0 = (OFF_Period >> 8);
		TL0 = OFF_Period;
	}	
			
}

void wait_door(void) interrupt 0
{

if(check_door)
    Delay_MS(2000);
}

void main()
{

    // diable the watch dog
    WDTCN = 0x0DE;
    WDTCN = 0x0AD;

    OSCICN = 0x014; // 2MH clock
    // config cross bar
    XBR0 = 0x00;
    XBR1 = 0x14; // enable interrupt crossbar
    XBR2 = 0x40;  // Cross bar enabled , weak Pull-up enabled

    EA = 1;  //enable global interrupt
    EX0 = 1; // enable external interrupt 0
    EX1 = 1; //enable external interrupt 1
    IT0 = 1;
    IT1 = 1;

    ET0 = 1; //enable interrupt of timer0
    ET1 = 1; //enable interrupt of timer1

    Timer_init();
    sevenSegment_write(0);
    //ET1 = 1; //enable interrupt of timer1

    // TL1 = 0xfb;
    // TH1 = 0xff;
    SERVO_Init();
    LED_Init(LED_1, LED_OFF);
    LED_Init(LED_2, LED_ON);
    // BUTTON_Init(BUTTON_OPEN);

    // Initialization of outside buttons
    button_init(BUTTON_4DOWN_PORT_dir, BUTTON_4DOWN_PIN);
    button_init(BUTTON_3DOWN_PORT_dir, BUTTON_3DOWN_PIN);
    button_init(BUTTON_3UP_PORT_dir, BUTTON_3UP_PIN);
    button_init(BUTTON_2DOWN_PORT_dir, BUTTON_2DOWN_PIN);
    button_init(BUTTON_2UP_PORT_dir, BUTTON_2UP_PIN);
    button_init(BUTTON_1DOWN_PORT_dir, BUTTON_1DOWN_PIN);
    button_init(BUTTON_1UP_PORT_dir, BUTTON_1UP_PIN);
    button_init(BUTTON_GUP_PORT_dir, BUTTON_GUP_PIN);

    // initialization of inside buttons
    button_init(BUTTON4_PORT_dir, BUTTON_4_PIN);
    button_init(BUTTON3_PORT_dir, BUTTON_3_PIN);
    button_init(BUTTON2_PORT_dir, BUTTON_2_PIN);
    button_init(BUTTON1_PORT_dir, BUTTON_1_PIN);
    button_init(BUTTONg_PORT_dir, BUTTON_G_PIN);

    // initialization of seven segment
    sevenSegment_init(sevenSeg_PORT_dir);

    while (1)
    {
        if(selectedFloor != currentFloor)
        {
            if (Direction == 1){
                elevatorUp();
                if(down_sum != 0)
                    elevatorDown();
            }
            else{
                elevatorDown();
                if(down_sum != 0)
                    elevatorUp();
            }
        }
    }
}

void getDirection()
{
if(selectedFloor != currentFloor)
        {
            if(selectedFloor > currentFloor)
            {
                up[selectedFloor] = 1;
                Direction = 1;

            }
            else 
            {
                down[selectedFloor] = 1;
                Direction = 0;
            }
        }

}
void setDirection(unsigned char x)
{
    if(moving == 0)
        Direction = x;

}

void elevatorUp()
{
    int floor = final_floor_up();
    int i = currentFloor;
    for (i ; i <= floor && (i != 5); i++)
    {
        // cycle = cycle + 2;
        // elevator up using dc motor
        moving = 1;
        sevenSegment_write(i); //print current floor on 7Seg
        Set_DutyCycle_To(cycle[i]);
        currentFloor = i;
        Delay_MS(250);
        // bringElevator();
        if (up[i] == 1)
        {   
            up[i] = 0;
            open_door();
        }
            
    }
    moving = 0;

    //open door( check if current floor = selected floor );
}

void elevatorDown()
{
    
    int floor = final_floor_down();
    int i = currentFloor;
    for (i; i >= floor; i--)
    {
        moving = 1;
        // cycle = cycle - 2;
        // elevator down using dc motor
        sevenSegment_write(i); //print current floor on 7Seg
        Set_DutyCycle_To(cycle[i]);
        currentFloor = i;
        Delay_MS(250);
        if (down[i] == 1)
        {
            down[i] = 0;
            open_door();
        }
        // bringElevator();

    }
    moving = 0;
    //open door( check if movingFlag = 0 );
}

unsigned char final_floor_up()
{
    if(up[4] == 1) 
        return 4;
    else if(up[3] == 1)
        return 3;
    else if(up[2] == 1)
        return 2;
    else if(up[1] == 1)
        return 1;
    else if(up[0] == 1)
        return 0;
    
}

unsigned char final_floor_down()
{
    if(down[0] == 1) 
        return 0;
    else if(down[1] == 1)
        return 1;
    else if(down[2] == 1)
        return 2;
    else if(down[3] == 1)
        return 3;
    else if(down[4] == 1)
        return 4;
    
}
void open_door()
{   
    check_door = 1;
    LED_Toggle(LED_1);
    LED_Toggle(LED_2);
    Delay_MS(1000);
    LED_Toggle(LED_1);
    LED_Toggle(LED_2);
    check_door = 0;
}

void Set_DutyCycle_To(float duty_cycle)
{
	float period = 65535 - PWM_Period;
	ON_Period = ((period/100.0) * duty_cycle);
	OFF_Period = (period - ON_Period);	
	ON_Period = 65535 - ON_Period;	
	OFF_Period = 65535 - OFF_Period;

}