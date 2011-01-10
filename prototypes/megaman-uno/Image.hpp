#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <algorithm>
#include <cmath>
#include "GameConfig.hpp"

SDL_Surface*	SDL_CreateSurface(int width, int height);
SDL_Surface*	SDL_SurfaceFlip(SDL_Surface* pSurface);
SDL_Surface*	SDL_SurfaceScale2x(SDL_Surface* pSurface);

class Image
{
	public:
		Image();
		Image(const char* file);
		Image(const Image& rhs);
		Image(Image* pImage, SDL_Rect& clip_rect);
		~Image();
		
		Image&	operator =(const Image& rhs);
		Image&	operator +=(const Image& rhs);
		
		const Image& operator +(const Image& rhs) const;
		
		bool	operator ==(const Image& rhs);
		
		int				GetWidth();
		int				GetHeight();
		SDL_Rect*		GetPosition();
		SDL_Surface*	GetSurface();
		SDL_Surface*	GetSurfaceFlip();
				
		void			SetColorKey(int red, int green, int blue);
		void			SetPosition(int x, int y);
		
		void			Load(const char* file);
		void			FreeMemory();
		
		void			FlipImage();
		void			Scale2x();
		
	private:
		SDL_Surface*	m_pImage;
		SDL_Surface*	m_pImageFlip;
		SDL_Rect		m_sPosition;
		Uint32			m_nColorkey;
};

#endif // _IMAGE_HPP_
