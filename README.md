# Elevator-system

**Elevator system using C8051F020 Silicon Lab Kit (8051 IC) and C Language**.

It is a simple elevator system with outside buttons for going up and going down, of course except the ground and the last floor, and inside 5 buttons for each floor.

### Components:
- 8051 Microcontroller
- LEDs
- One Seven-Segment
- Push Buttons
- Servo Motor
- Resistors

### Description of design circuit operation:

- Elevator’s each floor has two buttons one for going up, and one for going down except for the ground and last floor have one button only. 

- There are 5 buttons inside the elevator, one for each
floor.

- Whenever the elevator’s door is open it waits 5 seconds before it close again and the `green LED` is ON. 

- The elevator saves the requests of all the buttons, even when it’s going up and someone from outside pressed down button, it will go to its first destination and then back for the down call.

- The current floor is shown on a `seven segment`. 

- If someone blocks the door, we used `LDR sensor` to sense the presence of such case, in each time the door opens, in addition to setting a led to high as indication.

-  Also, we take overload issues into consideration for safety so we determine the maximum number of passengers can be in the elevator is four and if the number of passengers exceed four, another led for the door would also as our indicator. 
  
-  We used `FSR sensor` to sense if the maximum weight is reached by clicking on it more than four times as each time is indication for number of persons the voltage over the sensor will be compared with comparator. 