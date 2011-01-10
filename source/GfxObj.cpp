#include "GfxObj.h"

GfxObj::GfxObj(const GfxObj& go):
mp_plane(go.mp_plane),
m_row(go.m_row),
m_col(go.m_col)
{
   if( go.mp_row == &(go.m_row) )
   {
      // if go.mp_row references go.m_row, then mp_row just need to point to local m_row.
      mp_row = &m_row;
   }
   else
   {
      // if mp_row was set to point to a different variable we should copy the reference.
      mp_row = go.mp_row;
   }

   if( go.mp_col == &(go.m_col) )
   {
      mp_col = &m_col;
   }
   else
   {
      mp_col = go.mp_col;
   }
}

void GfxObj::SetClipRect(uint row, uint col, uint width, uint height)
{
   if( mp_rect ) delete mp_rect;
   mp_rect = new SDL_Rect;
   mp_rect->x = col;
   mp_rect->y = row;
   mp_rect->h = height;
   mp_rect->w = width;
}
