#ifndef __Video_h__
#define __Video_h__

/** Video subsystem main class.
    The main unit of processing is a Plane. Each application can have multiple 'stages' or 'scenarios', and
    these are composed by multiple planes of animation. Each plane possess multiple GfxObj (graphical objects)
    which are rendered in sequence and blitted in their container planes before the planes can be merged together
    and form an animation frame.
    @see Plane
*/

#include "Screen.h"
#include "Plane.h"

class Video
{
   public:
      /** Initialize video. */
      Video();
      /** Destructor. */
      ~Video();

      /** Prepare one stage for rendering.
          Each stage is stored in a script file which will be rendered by the video engine. This function
          reads this file and prepare the engine for rendering it to the screen.
          @param stage File name of the stage script as c-string.
      */
      void Prepare(const char* stage);
      /** Clear memory from last stage loaded. */
      void Finalize();
      /** Render next video frame. */
      void Update();

   private:
      Screen   m_screen;
      Plane*   mp_plane;
};

#endif // __Video_h__
