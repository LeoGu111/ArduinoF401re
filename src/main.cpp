#include <Arduino.h>

 typedef enum 
 { 
 SAFE_LOCKED,
 LEVEL_1,
 LEVEL_2,
 LEVEL_3,
 SAFE_OPEN,
 }
 State_t;

 typedef enum 
 {
 INPUT_1,
 INPUT_2,
 INPUT_3,
 OPEN_DOOR,
 CLOSE_DOOR,
 INPUT_REFUSED,
 } 
 Event_t;

State_t state = SAFE_LOCKED; // global variable 
Event_t event = INPUT_1;

void setup() 
{

}

void loop() 
{


}

void safe_states(Event_t event)
{
switch (state)
{
case SAFE_LOCKED:
  if (INPUT_1 == event)
  {
    state = LEVEL_1;
  }
  break;
case LEVEL_1:
  if (INPUT_2 == event)
  {
    state = LEVEL_2;
  }
  break;
case LEVEL_2:
  if (INPUT_3 == event)
  {
    state = LEVEL_3;
  }
  break;
case LEVEL_3:
  if (OPEN_DOOR == event)
  {
    state = SAFE_OPEN;
  }
  break;
case SAFE_OPEN:
  if (CLOSE_DOOR == event)
  {
    state = SAFE_LOCKED;
  }
  break;
}

if (INPUT_REFUSED && (LEVEL_1 == state || LEVEL_2 == state || LEVEL_3 == state))
{
  state = SAFE_LOCKED;
}

}