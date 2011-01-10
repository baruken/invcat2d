#include "Plane.hpp"

Plane::Plane()
{
	#ifdef DEBUG
	std::cout << "Plane constructor: " << this << std::endl;
	#endif
	
	SDL_Surface* video = SDL_GetVideoSurface();
	
	m_pSurface = SDL_CreateRGBSurface( 	video->flags,
										video->w,
										video->h,
										video->format->BitsPerPixel,
										video->format->Rmask,
										video->format->Gmask,
										video->format->Bmask,
										video->format->Amask );
	
	assert( m_pSurface != NULL );
	
	m_vpSprites.reserve(10);
}

Plane::~Plane()
{
	#ifdef DEBUG
	std::cout << "Plane destructor: " << this << std::endl;
	#endif
	
	SDL_FreeSurface(m_pSurface);
}

void Plane::AddToPlane(Sprite* pSprite)
{
	m_vpSprites.push_back(pSprite);
}

void Plane::Fill(int red, int green, int blue)
{
	SDL_Surface* video = SDL_GetVideoSurface();
	SDL_FillRect(m_pSurface, NULL, SDL_MapRGB(video->format, red, green, blue));
}

void Plane::Update()
{
	/* Plane update:
	 * 
	 * 1st - update the background and blit to m_pSurface
	 * 2nd - update each sprite and blit to m_pSurface
	 * 
	 * */
	
	std::vector<Sprite*>::const_iterator i;
	for(i = m_vpSprites.begin(); i != m_vpSprites.end(); i++)
	{
		(*i)->UpdateFrame();
		SDL_BlitSurface((*i)->GetCurrentFrame(), NULL, m_pSurface, (*i)->GetPosition());
	}
}

SDL_Surface* Plane::GetSurface()
{
	return m_pSurface;
}
