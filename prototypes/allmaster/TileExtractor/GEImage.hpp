#ifndef _GE_IMAGE_HEADER_
#define _GE_IMAGE_HEADER_

#include	"SDL/SDL.h"
#include	"SDL/SDL_image.h"

SDL_Surface* SurfaceScale2x(SDL_Surface* surface);

class GEImage
{
	public:
		// Creates image from file.
		GEImage(const char *file);
		// Creates an image by clipping another image.
		GEImage(GEImage* p_image, int width, int height, int nFrame);
		
		~GEImage();
	
		SDL_Surface*	GetSurface();
		SDL_Surface*	GetFlipSurface();
				
		void			SetColorKey(int R, int G, int B); // set "transparent" color
		
		int				GetWidth();
		int				GetHeight();
		
		void			Scale2x();
		
	private:
		SDL_Surface*	FlipSurface(SDL_Surface* flip_surface);
	
		SDL_Surface*	m_pSurface;
		SDL_Surface*	m_pFlipSurface;
		
		int				m_width;
		int				m_height;
};

#endif // _GE_IMAGE_HEADER_
