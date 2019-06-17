#include <vector>

struct NoteEvent
{
  int m_note;
  size_t m_time;
};

std::vector<NoteEvent> events;
size_t tick = 0;
size_t tick_loop_start = 0;
size_t first_event = 0;

#include "TouchInput.h"


TouchInput touch_1(0, 60);
TouchInput touch_2(1, 62);


int button_state_old = 0;
bool playing = false;
int m_last_played = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  button_state_old = digitalRead(2);   
}



void loop() {

  tick++;

  touch_1.update();
  touch_2.update();

  int button_state = digitalRead(2);
  if (button_state_old == 1 && button_state == 0)
  {
    Serial.println("loop start");
    Serial.println("Played: 0");
    playing = true;
    tick_loop_start = tick;
    m_last_played = 0;  
  }
  
  button_state_old = button_state;


  if (playing)
  {
    size_t loop_tick = tick - tick_loop_start;
/*
    Serial.print("now:");
    Serial.print(loop_tick);
    Serial.print("next note:");
    Serial.println(events[m_last_played+1].m_time - first_event);*/
    
    if (m_last_played + 1 < events.size() && loop_tick > events[m_last_played+1].m_time - first_event)
    {
      m_last_played++;
      Serial.print("Played:");
      Serial.println(events[m_last_played].m_note);
    }
  }
  
  
 
}
