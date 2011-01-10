#include "Surface.h"
#include "Config.h"
#include "SDL/SDL_image.h"
#include "Exception.h"
#include "Plane.h"

Surface::Surface():
mp_surface(0)
{

}

Surface::Surface(uint width, uint height):
GfxObj(),
mp_surface(0)
{
   mp_surface = SDL_CreateRGBSurface(CONFIG.SCR_Mode(),
                                     width,
                                     height,
                                     CONFIG.SCR_BPP(),
                                     RGB_RED,
                                     RGB_GREEN,
                                     RGB_BLUE,
                                     CONFIG.RGB_Alpha());

   if( !mp_surface )
   {
      stringstream ss;
      ss << "Unable to create surface. " << SDL_GetError()
         << " Width: " << width << " Height: " << height;

      throw Exception(EX_SDL, ss.str(), "(ctor)", "Surface");
   }

   if( CONFIG.SCR_TMode() == CK )
   {
      SDL_SetColorKey(mp_surface, SDL_SRCCOLORKEY, CONFIG.SCR_ColorKey(mp_surface));
   }
}

Surface::Surface(const char* file):
GfxObj(),
mp_surface(0)
{
   SDL_Surface* s;

   s = IMG_Load(file);
   if( !s )
   {
      stringstream ss;
      ss << "Unable to create surface. " << IMG_GetError()
         << " File: " << file;

      throw Exception(EX_SDL, ss.str(), "(ctor)", "Surface");
   }

   if( CONFIG.SCR_TMode() == PPA ) // optimizes image for current display resolution.
      mp_surface = SDL_DisplayFormatAlpha(s);
   else
      mp_surface = SDL_DisplayFormat(s);

   SDL_FreeSurface(s);
}

Surface::~Surface()
{
   if( mp_surface )
      SDL_FreeSurface(mp_surface);
}

Surface::Surface(const Surface& s):
GfxObj(s)
{
   if( CONFIG.SCR_TMode() == PPA) // make a copy of the surface
      mp_surface = SDL_DisplayFormatAlpha(s.mp_surface);
   else
      mp_surface = SDL_DisplayFormat(s.mp_surface);
}

void Surface::Blit(Surface& s)
{
   SDL_Rect position;
   position.x = *(s.mp_col);
   position.y = *(s.mp_row);

   if( SDL_BlitSurface(s.mp_surface,
                       s.mp_rect,
                       mp_surface,
                       &position) )
   {
      stringstream ss;
      ss << "Unable to blit surface. " << SDL_GetError();

      throw Exception(EX_SDL, ss.str(), "Blit()", "Surface");
   }
}

void Surface::Draw()
{
   mp_plane->Blit(*this);
}

void Surface::Save(const char* file)
{
   SDL_SaveBMP(mp_surface, file);
}

void Surface::FlipH()
{
   SDL_Surface* flip = SDL_SurfaceFlipH(mp_surface); // create left image
   delete mp_surface; // delete right image
   mp_surface = flip; // transfer left image to *this
}

void Surface::Scale2x()
{
   SDL_Surface* s2x = SDL_SurfaceScale2x(mp_surface); // create new 2x surface
   delete mp_surface; // delete old
   mp_surface = s2x; // transfer 2x surface to *this
}

SDL_Surface* SDL_SurfaceFlipH(SDL_Surface* flip_surface)
{
	SDL_Surface* copy_surface = NULL;

	if( flip_surface )
	{
		// This only works for 32 bit pixel format
		if( flip_surface->format->BitsPerPixel == 32 )
		{
			// This surface must be freed by the caller.
			copy_surface = SDL_CreateRGBSurface(flip_surface->flags, flip_surface->w, flip_surface->h,
											flip_surface->format->BitsPerPixel,
											flip_surface->format->Rmask,
											flip_surface->format->Gmask,
											flip_surface->format->Bmask,
											flip_surface->format->Amask);

			Uint32 *source = static_cast<Uint32*>(flip_surface->pixels);
			Uint32 *dest = static_cast<Uint32*>(copy_surface->pixels);

			for(int i = 0; i < flip_surface->h; i++)
			{
				for(int j = 0; j < flip_surface->w; j++)
				{
					dest[ i * flip_surface->w + j ] = source[ (i + 1) * flip_surface->w - j];
				}
			}
		}
	}

	return copy_surface;
}

SDL_Surface* SDL_SurfaceScale2x(SDL_Surface* surface)
{
   SDL_Surface* copy_surface = NULL;
	if( surface )
	{
		// This surface must be freed by the caller.
		copy_surface = SDL_CreateRGBSurface(surface->flags, surface->w * 2, surface->h * 2,
										surface->format->BitsPerPixel,
										surface->format->Rmask,
										surface->format->Gmask,
										surface->format->Bmask,
										surface->format->Amask);

		Uint32 *source = static_cast<Uint32*>(surface->pixels);
		Uint32 *dest = static_cast<Uint32*>(copy_surface->pixels);

		int index;
		int A, B, C, D, E, F, G, H, I;
		int E0, E1, E2, E3;

		for(int i = 0; i < surface->h; i++)
		{
			for(int j = 0; j < surface->w; j++)
			{
				index = i * surface->w + j;

				/*
				 * ABC
				 * DEF
				 * GHI
				 */

				E = index;
				B = (i == 0) ? E : E - surface->w;
				D = (j == 0) ? E : E - 1 ;
				F = (j == surface->w - 1) ? E : E + 1;
				H = (i == surface->h - 1) ? E : E + surface->w;
				A = (i == 0 && j == 0) ? E : (i == 0 && j != 0) ? B : ( i != 0 && j == 0) ? D : E - 1 - surface->w;
				C = (i == 0 && j == surface->w - 1) ? E : (i != 0 && j == surface->w - 1 ) ? B : (i == 0 && j != surface->w - 1) ? F : E + 1 - surface->w;
				G = (i == surface->h - 1 && j == 0) ? E : (i != surface->h - 1 && j == 0 ) ? H : (i == surface->h - 1 && j != 0) ? D : E - 1 + surface->w;
				I = (i == surface->h - 1 && j == surface->w - 1) ? E : (i != surface->h - 1 && j == surface->w - 1) ? H : (i == surface->h - 1 && j != surface->w - 1) ? F : E + 1 + surface->w;

				E0 = (i * 2) * copy_surface->w + (j * 2);
				E1 = E0 + 1;
				E2 = (1 + i * 2) * copy_surface->w + (j * 2);
				E3 = E2 + 1;

				if (source[B] != source[H] && source[D] != source[F])
				{
					dest[E0] = source[D] == source[B] ? source[D] : source[E];
					dest[E1] = source[B] == source[F] ? source[F] : source[E];
					dest[E2] = source[D] == source[H] ? source[D] : source[E];
					dest[E3] = source[H] == source[F] ? source[F] : source[E];
				}
				else
				{
					dest[E0] = source[E];
					dest[E1] = source[E];
					dest[E2] = source[E];
					dest[E3] = source[E];
				}
			}
		}
	}

	return copy_surface;
}
