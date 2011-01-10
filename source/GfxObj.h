#ifndef __GfxObj_h__
#define __GfxObj_h__

#include "Rect.h"
#include "MoveVector.h"

class Plane;

/** GfxObj stands for graphic object.
    Graphic objects are renderizable objects. These could be Sprites, Surfaces, Tiles, Effects and so on.
    Every renderizable object should inherit from this class and implement the pure virtual methods Draw(),
    Width() and Height().
    @autor Paulo A. Petruzalek
 */
class GfxObj : public Rect
{
   public:
      /** Default constructor.
          mp_col and mp_row always point to their local counterparts m_col and m_row.
          This can be overriden by SetColRef() and SetRowRef(). Used by Sprite constructor
          in order to every frame point to the current sprite position. Surface::Blit()
          function uses mp_col and mp_row rather than m_col and m_row to define blit
          position.
          @see SetColRef() SetRowRef() Sprite::Sprite() Surface::Blit()
      */
      GfxObj():m_row(0), m_col(0), mp_row(&m_row), mp_col(&m_col) {}
      GfxObj(const GfxObj& go);
      ~GfxObj() {}

      /** Print the object on it's plane.
          Each child of GfxObj should implement its update routine inside the Draw method.
          For instance, the sprite class should define its current frame on Draw method
          before printing itself to the current plane.
          It is also a good place to define object visibility, since one could decide to
          not draw the object inside this method. */
      virtual void   Draw() = 0;
      /** Returns object width. */
      virtual uint   Width() = 0;
      /** Returns object height. */
      virtual uint   Height() = 0;

      /** Set 'p' plane as owner of the object.
          This function should not be called directly. It is used in Plane::AddToPlane() in
          order to estabilish a bidirectional relation between the object and its plane.
          @param p Pointer to the object owner.
          @see Plane::AddToPlane() */
      inline void    SetPlane(Plane* p) { mp_plane = p; }
      /** Set object position in its plane.
          @param row Row (x coordinate) of object.
          @param col Column (y coordinate) of object.
       */
      inline void    SetPosition(uint row, uint col) { m_row = row; m_col = col; }

      /** Return 'x' (row) coordinate. */
      inline uint    Row() { return m_row; }
      /** Return 'y' (col) coordinate. */
      inline uint    Col() { return m_col; }

      /** Sets clipping rectangle in order to show only part of the object on its plane. */
      void           SetClipRect(uint row, uint col, uint width, uint height);

      /** Set object row reference to an external row variable.
          Used by Sprite so all sprite frames point to the same location.
          @see Sprite::Sprite()
      */
      void           SetRowRef(uint* p_row) { mp_row = p_row; }
      /** Set object col reference to an external col variable.
          Used by Sprite so all sprite frames point to the same location.
          @see Sprite::Sprite()
      */
      void           SetColRef(uint* p_col) { mp_col = p_col; }

   protected:
      Plane*      mp_plane;
      uint        m_row;
      uint        m_col;
      uint*       mp_row;
      uint*       mp_col;
      MoveVector  m_movevector;
};


#endif // __GfxObj_h__
