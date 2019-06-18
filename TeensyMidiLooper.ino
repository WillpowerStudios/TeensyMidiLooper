#include <vector>

struct NoteEvent
{
  int m_note;
  bool m_on;
  size_t m_time;
};

#include "TouchInputMIDI.h"
#include "Loop.h"

TouchInputMIDI touch_1(0, 60);
TouchInputMIDI touch_2(1, 62);
Loop loop1;
NoteEvent input_event;

int button_state_old = 0;

//-------------------------------------------------------------------------------
void setup() {
  
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  button_state_old = digitalRead(2);   
}

//-------------------------------------------------------------------------------
void loop() {

  loop1.update();
  
  if (touch_1.update(input_event))
  {
    loop1.addEvent(input_event);
  }
  
  if (touch_2.update(input_event))
  {
    loop1.addEvent(input_event);
  }

  int button_state = digitalRead(2);
  if (button_state_old == 1 && button_state == 0)
  {
    loop1.startPlayback();
  }
  
  button_state_old = button_state;

}
