#include <Arduino.h>

typedef enum
{
  SAFE_LOCKED,
  LEVEL_1,
  LEVEL_2,
  LEVEL_3,
  SAFE_OPEN,
} State_t;

typedef enum
{
  INPUT_1,
  INPUT_2,
  INPUT_3,
  OPEN_DOOR,
  CLOSE_DOOR,
  INPUT_REFUSED,
} Event_t;

void safe_states(Event_t event);

State_t state = SAFE_LOCKED; // global variable

void setup()
{
  pinMode(10, INPUT); // set pin to input
  pinMode(11, INPUT); // set pin to input
  pinMode(12, INPUT); // set pin to input
  pinMode(13, INPUT); // set pin to input

  digitalWrite(4, HIGH); // turn on pullup resistors
  digitalWrite(5, HIGH); // turn on pullup resistors
  digitalWrite(6, HIGH); // turn on pullup resistors
  digitalWrite(7, HIGH); // turn on pullup resistors
}

void loop()
{

  if (digitalRead(10))
  {
    safe_states(INPUT_1);
  }
  if (digitalRead(11))
  {
    safe_states(INPUT_2);
  }
  if (digitalRead(12))
  {
    safe_states(INPUT_3);
  }
  if (digitalRead(13))
  {
    safe_states(INPUT_REFUSED);
  }
}
void safe_states(Event_t event)
{
  switch (state)
  {
  case SAFE_LOCKED:
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

    if (INPUT_1 == event)
    {
      state = LEVEL_1;
    }

    break;
  case LEVEL_1:
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);

    if (INPUT_2 == event)
    {
      state = LEVEL_2;
    }
    else if (INPUT_REFUSED == event)
    {
      state = SAFE_LOCKED;
    }

    break;
  case LEVEL_2:
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);

    if (INPUT_3 == event)
    {
      state = LEVEL_3;
    }
    else if (INPUT_REFUSED == event)
    {
      state = SAFE_LOCKED;
    }

    break;
  case LEVEL_3:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    
    if (OPEN_DOOR == event)
    {
      state = SAFE_OPEN;
    }
    else if (INPUT_REFUSED == event)
    {
      state = SAFE_LOCKED;
    }
    break;
  case SAFE_OPEN:
    if (CLOSE_DOOR == event)
    {
      state = SAFE_LOCKED;
    }
    break;
  }
}