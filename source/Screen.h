#ifndef __Screen_h__
#define __Screen_h__

#include "Surface.h"
#include "SDL/SDL.h"

/** Software representation of the system screen.
    Implemented as a custom Surface. There should be only
    one screen per application.
    @see Surface
*/
class Screen : public Surface
{
   public:
      /** Create the screen surface.
          This constructor also uses parameters defined in 'config.ini' accessed by the
          CONFIG macro.
          @see Config.h
      */
      Screen();
      /** Default destructor. */
      ~Screen();

      /** Assignment operator.
          Use this operator to plot a surface to the screen. This should be the last step
          when displaying an animation frame. Usually called from the Video class.
          @param s Surface to be displayed on screen.
          @see Video.h Surface.h
      */
      void operator=(Surface& s);

      /** Hides Surface::Draw(). */
      void Draw() {}

   private:
      Screen(const Screen&);

};

#endif // __Screen_h__
