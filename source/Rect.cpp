#include "Rect.h"

Rect::Rect():
mp_rect(0)
{
}

Rect::Rect(uint row, uint col, uint width, uint height)
{
   mp_rect = new SDL_Rect;
   mp_rect->x = col;
   mp_rect->y = row;
   mp_rect->h = height;
   mp_rect->w = width;
}

Rect::~Rect()
{
   if(mp_rect) delete mp_rect;
}

