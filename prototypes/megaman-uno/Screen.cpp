#include "Screen.hpp"

Screen::Screen(int width, int height, int bitsperpixel, int flags)
{
	#ifdef DEBUG
	std::cout << "Screen constructor: " << this << "\n";
	#endif
	
	m_pScreen = SDL_SetVideoMode(width, height, bitsperpixel, flags);
	assert( m_pScreen != NULL );
}

Screen::~Screen()
{
	#ifdef DEBUG
	std::cout << "Screen destructor: " << this << "\n";
	#endif
}

int Screen::GetHeight()
{
	return m_pScreen->h;
}

int Screen::GetWidth()
{
	return m_pScreen->w;
}

void Screen::Display(SDL_Surface* pSurface)
{
	if( m_Timer.GetTicks() < 1000 / SCREEN_FRAME_RATE )
	{
		SDL_Delay( (1000 / SCREEN_FRAME_RATE) - m_Timer.GetTicks() );
	}
	
	SDL_BlitSurface(pSurface, NULL, m_pScreen, NULL);
	SDL_Flip(m_pScreen);
	
	m_Timer.Start();
}

void Screen::FadeOut()
{
	Uint32 black = SDL_MapRGB(m_pScreen->format, 0x00, 0x00, 0x00);
	
	SDL_Surface* black_surface = SDL_CreateRGBSurface(	m_pScreen->flags,
														m_pScreen->w,
														m_pScreen->h,
														m_pScreen->format->BitsPerPixel,
														m_pScreen->format->Rmask,
														m_pScreen->format->Gmask,
														m_pScreen->format->Bmask,
														0);
														
	assert( black_surface != NULL );
	
	SDL_FillRect(black_surface, NULL, black);
														
	for(int i = 0; i < 128; i +=5)
	{
		SDL_SetAlpha(black_surface, SDL_SRCALPHA, i);
		Display(black_surface);
	}
	
	SDL_FreeSurface(black_surface);
}

void Screen::FadeIn(SDL_Surface* pSurface)
{
	Uint32 black = SDL_MapRGB(m_pScreen->format, 0x00, 0x00, 0x00);
	
	SDL_Surface* black_surface = SDL_CreateRGBSurface(	m_pScreen->flags,
														m_pScreen->w,
														m_pScreen->h,
														m_pScreen->format->BitsPerPixel,
														m_pScreen->format->Rmask,
														m_pScreen->format->Gmask,
														m_pScreen->format->Bmask,
														0);
														
	assert( black_surface != NULL );
	
	SDL_FillRect(black_surface, NULL, black);
														
	for(int i = 0; i < 128; i += 5)
	{
		SDL_SetAlpha(pSurface, SDL_SRCALPHA, i);
		SDL_BlitSurface(pSurface, NULL, black_surface, NULL);
		Display(black_surface);
	}
	
	SDL_FreeSurface(black_surface);	
}
