#include "GECollisionManager.hpp"

GECollisionManager::GECollisionManager():
m_pCollisionMap(NULL),m_nCharacterCount(0), m_pPlaneMap(NULL)
{
	SDL_Surface* video = SDL_GetVideoSurface();
	
	m_nCollisionMask = SDL_MapRGB(video->format, GE_COLLISIONMASK_R, GE_COLLISIONMASK_G, GE_COLLISIONMASK_B);
	m_nColorKey = SDL_MapRGB(video->format, GE_COLORKEY_R, GE_COLORKEY_G, GE_COLORKEY_B);
}

GECollisionManager::~GECollisionManager()
{
	if( m_pCollisionMap ) SDL_FreeSurface(m_pCollisionMap);
}

void GECollisionManager::Update()
{
	// Test for scenario collision
	for(int i = 0; i < m_nCharacterCount; i++)
	{
		m_pCharacters[i]->UpdateInput();

		// Check left and right
		if( IsOnWall(m_pCharacters[i]) )
		{
			m_pCharacters[i]->Stand();
		}

		// Check down
		if( IsOnGround(m_pCharacters[i]) )
		{
			// Land do nothing if character is already on ground level
			m_pCharacters[i]->Land();
		}
		else
		{
			m_pCharacters[i]->Fall();
		}
		
		// Check up
		if( IsOnRoof(m_pCharacters[i]) )
		{
//			m_pCharacters[i]->Fall();
		}
				
		m_pCharacters[i]->UpdateFrame();
	}
	
	// Test for sprite x sprite collision
	for(int i = 0; i < m_nCharacterCount; i++)
	{
		for(int j = 0; i < m_nCharacterCount; i++)
		{
			if(i == j) continue;
			if( (m_pCharacters[i] == NULL) || (m_pCharacters[j] == NULL) ) continue;
			if( IntersectRect(m_pCharacters[i]->GetPosition(), m_pCharacters[j]->GetPosition()) )
			{
				// i collides with j
				
			}
		}
	}
}

bool GECollisionManager::IntersectRect(SDL_Rect* rect1, SDL_Rect* rect2)
{
	int rect1_left = rect1->x;
	int rect1_right = rect1_left + rect1->w;
	int rect1_up = rect1->y;
	int rect1_down = rect1_up + rect1->h;
	
	int rect2_left = rect2->x;
	int rect2_right = rect2_left + rect2->w;
	int rect2_up = rect2->y;
	int rect2_down = rect2_up + rect2->h;
	
	if( rect1_right < rect2_left) return false;
	if( rect2_right < rect1_left) return false;
	if( rect1_up < rect2_down ) return false;
	if( rect2_up < rect1_down ) return false;
	
	return true;
}

bool GECollisionManager::IsOnGround(GECharacter* pCharacter)
{
	SDL_Rect* boundaries = pCharacter->GetPosition();
	bool bContact = false;
	
	int	nMapWidth = m_pCollisionMap->w;
	
	Uint32*	map = static_cast<Uint32*>(m_pCollisionMap->pixels);
	
	// y = top , adds height to get the bottom, adds 1 to get the line just below
	// index = (y+h)*width + (x+w)
	int	map_index = (boundaries->y + boundaries->h + 1) * nMapWidth + boundaries->x;

	for(int i = 0; i < boundaries->w; i++)
	{
		if( map[map_index+i] == m_nCollisionMask )
		{
			bContact = true;
				
			break;
		}
	}
		
	return bContact;
}

bool GECollisionManager::IsOnRoof(GECharacter* pCharacter)
{
/*	SDL_Rect* boundaries = pCharacter->GetPosition();
	bool bContact = false;
	
	int	nMapWidth = m_pPlaneMap->w;
	
	Uint32* source = static_cast<Uint32*>pCharacter->GetSurface()->pixels;
	
	// For the width of the sprite, test if there is contact with the surface
	for(int i = 0; i < boudaries->w; i++)
	{
		// y = top , adds height to get the bottom, adds 1 to get the line just below
		
		if( (m_pCollisionMap[ (boudaries->y + boundaries->h + 1) * nMapWidth + (boundaries.y + i)] == m_nColisionMask ) && source[ (boundaries.h - 1) * boundaries.w + i ] != m_nColorKey )
		{
			// just need one pixel contact to confirm collision
			bContact = true;
			break;
		}
	}
	
	return bContact;*/
}

bool GECollisionManager::IsOnWall(GECharacter* pCharacter)
{
	bool bContact = false;
	SDL_Rect* boundaries = pCharacter->GetPosition();
	
	int	nMapWidth = m_pCollisionMap->w;	
	int	nMapIndex = boundaries->y * nMapWidth + boundaries->x;
	
	pCharacter->GetDirection() == GE_SPRITE_FACING_LEFT ? nMapIndex-- : nMapIndex += boundaries->w + 1;
	
	Uint32*	map = static_cast<Uint32*>(m_pCollisionMap->pixels);
	
	// For the height of the sprite, test if there is contact with the surface
	for(int i = 0; i < boundaries->h; i++)
	{
		// x = left , adds width to get right (x+w)
		// subtract 1 from left or adds 1 to right to get the adjacent col
		if( map[nMapIndex + i*nMapWidth] == m_nCollisionMask ) // is possible to optimize this code by removing the multiplication in the index (index += mapwidth)
		{
			bContact = true;

			break;
		}
	}
	
	return bContact;
}


void GECollisionManager::BuildCollisionMap(GEPlaneMap* pPlaneMap)
{
	if( m_pCollisionMap ) SDL_FreeSurface(m_pCollisionMap);
	
	SDL_Surface* video = NULL;
	video = SDL_GetVideoSurface();
	
	m_pPlaneMap = pPlaneMap;
	
	int nWidth = pPlaneMap->GetSurface()->w;
	int nHeight = pPlaneMap->GetSurface()->h;
	
	// The collision map has the same dimensions of the plane map
	m_pCollisionMap = SDL_CreateRGBSurface(	video->flags, nWidth, nHeight,
											video->format->BitsPerPixel, 
											video->format->Rmask, 
											video->format->Gmask, 
											video->format->Bmask, 
											video->format->Amask);
	
	Uint32* source = static_cast<Uint32*>(pPlaneMap->GetSurface()->pixels);
	Uint32* dest = static_cast<Uint32*>(m_pCollisionMap->pixels);
	
	for(int i = 0; i < nHeight; i++)
	{
		for(int j = 0; j < nWidth; j++)
		{
			if( source[i*nWidth + j] == m_nColorKey )
			{
				dest[i*nWidth + j] = 0;
			}
			else
			{
				dest[i*nWidth + j] = m_nCollisionMask;
			}
		}
	} // The collision map only have two colors => black(empty) and red(filled);
	
	// debug!
	// SDL_SaveBMP(m_pCollisionMap, "collision_map.bmp");
}

void GECollisionManager::AddCharacter(GECharacter* pCharacter)
{
	// TODO: A proper list
	m_pCharacters[m_nCharacterCount++] = pCharacter;
}

int GECollisionManager::GetCharacterCount()
{
	return m_nCharacterCount;
}

GECharacter* GECollisionManager::GetCharacter(int nIndex)
{
	return m_pCharacters[nIndex];
}

SDL_Surface* GECollisionManager::GetCollisionMap()
{
	return m_pCollisionMap;
}

void GECollisionManager::FixPosition(GECharacter* pCharacter)
{
	//UP
	
	/*	for(int j = 0; j < boundaries->h; j++)
			{
				map_index -= nMapWidth; // roll back one line at a time
				if(map_index < 0) break; // Avoid off map checking
				
				for(int k = 0; k < boundaries->w; k++)
				{
					if( map[map_index+k] == m_nCollisionMask )
					{
						boundaries->y--; // was IN the solid, roll back
						std::cout << "Sprite position corrected: " << boundaries->y << "\n";
						break; // only one pixel is needed
					}
				}
			}
	*/
	
	// LEFT & RIGHT
	
	/*		for(int j = 0; j < boundaries->w; j++)
			{
				pCharacter->GetDirection() == GE_SPRITE_FACING_LEFT ? nMapIndex++ : nMapIndex--;
				
				for(int k = 0; k < boundaries->h; k++)
				{
					if( map[nMapIndex+k*nMapWidth] == m_nCollisionMask )
					{
						pCharacter->GetDirection() == GE_SPRITE_FACING_LEFT ? boundaries->x++ : boundaries->x--; // was IN the solid, roll back
						break; // only one pixel is needed
					}
				}
			}
	*/	
}
