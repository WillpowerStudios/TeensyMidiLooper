
class TouchInput
{
  static const int thresh = 2200;
  static const int delay_time = 3;
  
  public:

  TouchInput(int pin, int note)
  : m_pin(pin)
  , m_note(note)
  {
    m_touched = touchRead(m_pin) > thresh;
  }

  void update()
  {
    bool touched = touchRead(m_pin) > thresh;

    if (touched && !m_touched) {
      usbMIDI.sendNoteOn(m_note, 80, 1);
      delay(delay_time); 
      m_touched = true;

      NoteEvent event;
      event.m_note = m_note;
      event.m_time = tick;

      events.emplace_back(event);

      if (events.size() == 1)
      {
        first_event = tick;
      }

      Serial.println(events.size());
    }
    else if (!touched && m_touched) {
      usbMIDI.sendNoteOff(m_note, 0, 1);
      delay(delay_time); 
      m_touched = false;
      //Serial.println("!touched");
    }

  }

  private:

  int m_pin = 0;
  int m_note = 0;
  bool m_touched = false;
};
