#ifndef _GE_COLLISIONMANAGER_HEADER_
#define _GE_COLLISIONMANAGER_HEADER_

#include "SDL/SDL.h"
#include "GEConstants.hpp"
#include "GECharacter.hpp"
#include "GEPlaneMap.hpp"

#include <iostream>

/* Collision Mechanics
 * 
 * The collision manager keeps track of all the characters position on and off-screen.
 * When two characters collide, it does the proper actions like damage calculation.
 * 
 * For the purpouse of the current implementation, every moving object is a character
 * (shots, traps, npcs and so on).
 * 
 * Every Animated Object should have a collision type associated:
 * GE_COLLISION_SOLID 		= will collide with other solid
 * GE_COLLISION_SEMISOLID 	= will collide with solid but not with semisolid
 * GE_COLLISION_LIQUID		= will collide with solid, semisolid and liquid
 * GE_COLLISION_GASOSE		= will collide only with gasose
 * GE_COLLISION_NONE		= doesn't collide
 * 
 * */

class GECollisionManager
{
	public:
		GECollisionManager();
		~GECollisionManager();
	
		// Prepare collision map from plane map using GE_COLORKEY_*
		void		BuildCollisionMap(GEPlaneMap* pPlaneMap);
		
		// Handles sprites and other objects
		void		AddCharacter(GECharacter* pCharacter);
		void		RemoveFromCollisionMap(GECharacter* pCharacter);
		void		ClearCollisionMap(); // clear all
		
		int				GetCharacterCount();
		GECharacter*	GetCharacter(int nIndex);
		SDL_Surface*	GetCollisionMap();
		
		bool		IsOnGround(GECharacter* pCharacter);
		bool		IsOnRoof(GECharacter* pCharacter);
		bool		IsOnWall(GECharacter* pCharacter);
			
		void		Update();
			
	private:
		bool		IntersectRect(SDL_Rect* pRect1, SDL_Rect* pRect2);
		bool		PixelRectCollision(SDL_Rect* pPixel, SDL_Rect* pRect);
	
		// All the "sprites" on screen
		GECharacter*	m_pCharacters[GE_CHARACTER_LIMIT];
		int				m_nCharacterCount;
		
		SDL_Surface*	m_pCollisionMap;
		GEPlaneMap*		m_pPlaneMap;
		
		Uint32			m_nCollisionMask;
		Uint32			m_nColorKey;
};


#endif // _GE_COLLISIONMANAGER_HEADER_
