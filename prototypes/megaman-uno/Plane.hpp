#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include <vector>
#include "GameConfig.hpp"
#include "Sprite.hpp"

class Plane
{
	public:
		Plane();
		~Plane();
		
		void			AddToPlane(Sprite* pSprite);
		void			Fill(int red, int green, int blue);
		
		SDL_Surface* 	GetSurface();
		
		void			Update();
		
	private:
		SDL_Surface* 			m_pSurface;
		std::vector<Sprite*>	m_vpSprites;
};

#endif // _PLANE_HPP_
