#ifndef __KbInput_h__
#define __KbInput_h__

#include "SDL/SDL.h"
#include "Input.h"

/** Keyboard input.
    Implements input interface for keyboard device.
    @see Input
*/

class KbInput : public Input
{
   public:
      KbInput();
      ~KbInput();

      bool  Up();
      bool  Down();
      bool  Left();
      bool  Right();
      bool  Escape();
      bool  Enter();
      bool  Pause();
      bool  Select();
      bool  Action(uint action);

   private:
      Uint8*   mp_keystates;

      int   m_up;
      int   m_down;
      int   m_left;
      int   m_right;
      int   m_escape;
      int   m_enter;
      int   m_pause;
      int   m_select;
      int   m_num_actions;
      int*  mp_actions;
};

#endif // __KbInput_h__
