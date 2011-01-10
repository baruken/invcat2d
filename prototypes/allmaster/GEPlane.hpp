#ifndef _GE_PLANE_HEADER_
#define _GE_PLANE_HEADER_

#include "SDL/SDL.h"
#include "GEConstants.hpp"
#include "GECharacter.hpp"
#include "GEPlaneMap.hpp"
#include "GEMoveVector.hpp"
#include "GECollisionManager.hpp"
#include <iostream>

#include "SDL/SDL_ttf.h"

class GEPlane
{
	public:
		GEPlane(Uint32 flags);
		~GEPlane();
	
		// Plane set up
		void	AddCharacter(GECharacter* pCharacter);
		void	SetPlaneMap(GEPlaneMap* plane_map);
		void	SetPlaneSpeed(int speed);
		void	SetMoveVector(GEMoveVector* m_pMoveVector);
		
		// Plane screenshot
		SDL_Surface* 	GetSurface();
		
		// Update the plane using the movement coordinated by move_vector
		void			Update();
		
	private:
		SDL_Surface*	m_pPlane;
		SDL_Rect		m_position;
		
		int		m_nSpeed;
		int		m_nMapWidth;
		int		m_nMapHeight;
		
		GEPlaneMap*			m_pPlaneMap;
		GECollisionManager* m_pCollisionManager;
		GEMoveVector*		m_pMoveVector;
};

#endif // _GE_PLANE_HEADER_
