#ifndef __Surface_h__
#define __Surface_h__

/** Surface class represents a 2 dimensional image.
    The surface is a 2D image derived from GfxObj. It is also the basic unit of the engine, since most of
    the animations are based on superposition of surfaces. Planes currently are also implemented using
    surfaces.
    @see GfxObj Plane
 */

#include "GfxObj.h"

class Surface : public GfxObj
{
   public:
      /** Default constructor.
          Creates a null surface. This constructor is used by Screen() and should not be used anywhere else.
      */
      Surface();
      /** Creates a surface with determined size.
          This should be the preferred method for creating empty surfaces.
          @param width Surface width.
          @param height Surface height.
      */
      Surface(uint width, uint height);
      /** Creates a surface from a file.
          Loads the image and its parameters from file. Uses IMG_Load library, so it currently supports
          BMP, PNG and TGA files.
          Note: per-pixel alpha (PPA) should be set in 'config.ini' in order to work with PNG and TGA images.
          @param file File name as a c-string.
          @see Config.h
      */
      Surface(const char* file);
      /** Copy constructor.
          Clones 's' surface.
      */
      Surface(const Surface& s);
      /** Destructor. */
      ~Surface();

      /** Makes a copy of 's' surface into target surface (self).
          It's the main drawing function to build complex animations. The source surface size and position is used in
          order to blit the surface, meaning that the source position is relative to the target surface. The entire
          target surface area is available for blitting (meaning that target clip rect won't apply).
          @param s Source surface. Note: target surface is self.
          @see Rect GfxObj
      */
      void        Blit(Surface& s);

      /** Plot surface into owner (plane).
          In order to call Draw() one must first assign the surface to a plane by calling Plane::AddToPlane().
          This function will blit itself to the plane it belongs, assuming row and col positions inherited from GfxObj.
          These position coordinate are always relative to the plane.
          @see GfxObj Plane
      */
      void        Draw();
      /** Returns Surface width. */
      inline uint Width() { return mp_surface->w; }
      /** Returns Surface height. */
      inline uint Height() { return mp_surface->h; }
      /** Save surface to BMP file. */
      void        Save(const char* file);

      /** Mirror the surface horizontally.
          A left image becomes a right image and vice-versa
      */
      void        FlipH();
      /** Upscale the surface by 2x.
          Applies Scale2x algoritmn to the surface. Each time the function is called the area is doubled.
      */
      void        Scale2x();

   protected:
      SDL_Surface* mp_surface;

};

/** Flip the surface horizontally.
    Returns a copy of the surface with its pixels inverted. The flipped surface must be freed by the caller
    with operator delete.
*/
SDL_Surface* SDL_SurfaceFlipH(SDL_Surface* flip_surface);
/** Upscale surface by 2x.
    Returns a copy of the surface with 2x filter applied. The scaled surface must be freed by the caller with
    operator delete.
*/
SDL_Surface* SDL_SurfaceScale2x(SDL_Surface* surface);

#endif // __Surface_h__
