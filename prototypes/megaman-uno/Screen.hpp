#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include "GameConfig.hpp"
#include "Timer.hpp"

class Screen
{
	public:
		Screen(int width, int height, int bitsperpixel, int flags);
		~Screen();
		
		void				Display(SDL_Surface* pSurface);
		void				FadeIn(SDL_Surface* pSurface);
		void				FadeOut();
				
		int					GetBitsPerPixel();
		int					GetFlags();
		int					GetHeight();
		int					GetWidth();
		SDL_PixelFormat*	GetPixelFormat();
		
	private:
		SDL_Surface*		m_pScreen;
		Timer				m_Timer;
};


#endif
