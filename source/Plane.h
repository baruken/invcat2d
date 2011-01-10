#ifndef __Plane_h__
#define __Plane_h__

#include "Surface.h"
#include <vector>

using namespace std;

/** Represents a drawing plane.
    Every animation frame is composed by a superposition of frames, and every animated object should
    be associated with a plane in order to be rendered to the screen.
    @see Surface Video GfxObj
*/

class Plane : public Surface
{
   public:
      Plane(uint width, uint height);
      ~Plane();

      /** Adds a GfxObj to the plane.
          Ownership is transfered to the plane object. The caller should not delete the object
          after this call. The objects will be deleted in the plane destructor.
          Also, the objects added to the plane are rendered in the order they are added. So,
          background should be added before sprites and other objects.
          @param go The GfxObj to be added.
          @see GfxObj
      */
      void  AddToPlane(GfxObj* go);
      /** Form a plane image by composing all GfxObj contained within the plane.
          @see GfxObj
      */
      void  Draw();

      friend class Video;

   private:
      Plane();

      vector<GfxObj*> map_gfxobj;
};

#endif // __Plane_h__
