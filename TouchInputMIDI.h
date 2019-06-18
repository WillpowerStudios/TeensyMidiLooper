
class TouchInputMIDI
{
  static const int thresh = 2200;
  static const int delay_time = 3;
  
  public:

  //-------------------------------------------------------------------------------
  TouchInputMIDI(int pin, int note)
  : m_pin(pin)
  , m_note(note)
  {
    m_touched = touchRead(m_pin) > thresh;
  }

  //-------------------------------------------------------------------------------
  // returns true when state changed
  bool update(NoteEvent &event)
  {
    bool touched = touchRead(m_pin) > thresh;

    // Touched
    if (touched && !m_touched) {

      usbMIDI.sendNoteOn(m_note, 80, 1);
      delay(delay_time); 
      m_touched = true;
      //Serial.println(events.size());

      event.m_note = m_note;
      event.m_on = true;
      event.m_time = millis();
      
      return true;
    }
    // Released
    else if (!touched && m_touched) {
      usbMIDI.sendNoteOff(m_note, 0, 1);
      delay(delay_time); 
      m_touched = false;
      //Serial.println("!touched");

      event.m_note = m_note;
      event.m_on = false;
      event.m_time = millis();
      
      return true;
    }

    return false;

  }

  private:

  int m_pin = 0;
  int m_note = 0;
  bool m_touched = false;
};
