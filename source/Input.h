#ifndef __Input_h__
#define __Input_h__

#include "Types.h"

/** Interface for input devices.
    Input is a pure virtual class that defines the basic interface for every input device.
    @see KbInput
*/

class Input
{
   public:
      virtual bool  Up() = 0;
      virtual bool  Down() = 0;
      virtual bool  Left() = 0;
      virtual bool  Right() = 0;

      virtual bool  Action(uint action) = 0;

      virtual bool  Escape() = 0;
      virtual bool  Enter() = 0;
      virtual bool  Pause() = 0;
      virtual bool  Select() = 0;
};

#endif // __Input_h__
