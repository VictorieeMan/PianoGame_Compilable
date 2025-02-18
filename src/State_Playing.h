
// Copyright (c)2007 Nicholas Piegdon
// See license.txt for license information

#ifndef __STATE_PLAYING_H
#define __STATE_PLAYING_H

#include <string>
#include <vector>
#include <set>

#include "SharedState.h"
#include "GameState.h"
#include "KeyboardDisplay.h"

struct TrackProperties;
class Midi;
class MidiCommOut;
class MidiCommIn;

struct ActiveNote
{
   bool operator()(const ActiveNote &lhs, const ActiveNote &rhs) const
   {
      if (lhs.note_id < rhs.note_id) return true;
      if (lhs.note_id > rhs.note_id) return false;

      if (lhs.channel < rhs.channel) return true;
      if (lhs.channel > rhs.channel) return false;

      return false;
   }

   NoteId note_id;
   unsigned char channel;
   int velocity;
};
typedef std::set<ActiveNote, ActiveNote> ActiveNoteSet;

class PlayingState : public GameState
{
public:
   PlayingState(const SharedState &state);
   ~PlayingState();

protected:
   virtual void Init();
   virtual void Update();
   virtual void Draw(Renderer &renderer) const;

private:

   int CalcKeyboardHeight() const;
   void SetupNoteState();

   void ResetSong();
   void Play(microseconds_t delta_microseconds);
   void Listen();

   double CalculateScoreMultiplier() const;

   bool m_paused;

   KeyboardDisplay *m_keyboard;
   microseconds_t m_show_duration;
   TranslatedNoteSet m_notes;

   bool m_any_you_play_tracks;
   size_t m_look_ahead_you_play_note_count;

   ActiveNoteSet m_active_notes;

   bool m_first_update;

   SharedState m_state;
   int m_current_combo;

   double m_title_alpha;
   double m_max_allowed_title_alpha;

   // For octave sliding
   int m_note_offset;
};

#endif
