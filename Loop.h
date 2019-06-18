
class Loop
{
  public:

  //void startRecording();
  //-------------------------------------------------------------------------------
  void addEvent(NoteEvent event)
  {
    if (m_playing) { 
      return; // get out 
    }
    
    if (m_events.size() == 0)
    {
      m_time_record = event.m_time;
    }

    event.m_time -= m_time_record;

    m_events.emplace_back(event);
  }
  //void stopRecording();

  //-------------------------------------------------------------------------------
  void startPlayback()
  {
    m_playing = true;
    m_time_playback = millis();
    m_last_note_played = -1;
  }

  //-------------------------------------------------------------------------------
  void update()
  {
    if (m_playing)
    {
      int next_note_index = m_last_note_played + 1;
      NoteEvent next_note = m_events[next_note_index];
      if (millis() >= m_time_playback + next_note.m_time)
      {
        int note = next_note.m_note;
        if (next_note.m_on)
        {
          usbMIDI.sendNoteOn(note, 80, 1);
        }
        else
        {
          usbMIDI.sendNoteOff(note, 0, 1);          
        }

        m_last_note_played++;
        
        if (m_last_note_played == m_events.size() - 1)
        {
          startPlayback();
        }
      }
    }
  }
  
  //void stopPlayback();

  private:

  std::vector<NoteEvent> m_events;
  size_t m_time_playback = 0;
  size_t m_time_record = 0;
  bool m_playing = false;
  int m_last_note_played = -1;

};
