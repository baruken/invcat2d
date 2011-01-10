#ifndef _GE_SCREEN_HEADER_
#define _GE_SCREEN_HEADER_

#include "SDL/SDL.h"
#include "GEPlane.hpp"
#include "GEMoveVector.hpp"

class GEScreen
{
	public:
		GEScreen();
		~GEScreen();
		
		// Level building
		void	AddToPlane(int nPlane, GECharacter* pCharacter);
		void	SetPlaneMap(int nPlane, GEPlaneMap* pPlaneMap);
		
		// Screen control
		void	SetMoveVector(GEMoveVector* move_vector);
		
		// Updates screen
		void	Display();
		
	private:
		SDL_Surface*	m_pScreen;
		GEPlane*		m_pPlanes[GE_SCREEN_MAX_PLANES];
};

#endif // _GE_SCREEN_HEADER_
