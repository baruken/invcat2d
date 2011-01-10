#ifndef __Rect_h__
#define __Rect_h__

#include "SDL/SDL.h"
#include "Types.h"

/** Rectangle class.
*/
class Rect
{
   public:
      /** Default constructor. Create a NULL rect. */
      Rect(); // null rect
      /** Build a Rect with given position and dimensions. */
      Rect(uint row, uint col, uint width, uint height);
      ~Rect();

      friend class   Surface;

   protected:
      SDL_Rect* mp_rect;
};

#endif // __Rect_h__
