#include "GESprite.hpp"

const int GE_SPRITE_DEFAULT_ACTION[] = { 0, -1 };

// Create sprite from file (with nFrames images)
GESprite::GESprite(const char* file, int width, int height)
{
	std::cout << "GESprite constructor. File = " << file << '\n';
	std::cout << "Sprite parameters: width = " << width << " height = " << height << '\n';
	GEImage* temp_image = NULL;
	temp_image = new GEImage(file);
	
	m_nTotalFrames = temp_image->GetWidth() / width;
	std::cout << "Frames found: " << m_nTotalFrames;
		
	// Limit number of sprites loaded from map.
	if( m_nTotalFrames > GE_SPRITE_MAX_FRAMES ) m_nTotalFrames = GE_SPRITE_MAX_FRAMES;
	std::cout << " Frames loaded: " << m_nTotalFrames << '\n';
	
	m_nWidth = width;
	m_nHeight = height;
		
	for(int i = 0; i < m_nTotalFrames; i++)
	{
		m_pFrames[i] = new GEImage(temp_image, width, height, i);
	}

	delete temp_image;
	
	Init();
}

void GESprite::Init()
{
	std::cout << "GESprite::Init()\n";

	m_nCurrentFrame = 0;
	m_pDefaultAction = const_cast<GESpriteAction>(GE_SPRITE_DEFAULT_ACTION);
	m_pCurrentAction = m_pDefaultAction;
	m_nCurrentActionPos = 0;
	m_nRepeatActionPos = 0;
	
	m_bVisible = false;
	m_eDirection = GE_SPRITE_FACING_RIGHT;
}

GESprite::~GESprite()
{
	std::cout << "GESprite destructor.\n";
	for(int i = 0; i < m_nTotalFrames; i++)
	{
		delete m_pFrames[i];
	}
}

int GESprite::GetWidth()
{
	return m_nWidth;
}

int GESprite::GetHeight()
{
	return m_nHeight;
}

SDL_Surface* GESprite::GetCurrentFrame()
{
	if( m_bVisible )
	{
		if( m_eDirection == GE_SPRITE_FACING_LEFT )
		{
			return m_pFrames[m_nCurrentFrame]->GetFlipSurface();
		}
		else
		{
			return m_pFrames[m_nCurrentFrame]->GetSurface();
		}
	}
	else
	{	// A SDL_BlitSurface call with NULL will blit nothing.
		return NULL;
	}
}

// Action example:
// 				attack[3] = {1, 2, -1};
//				walk[4] = {3, 4, 3, 5, -1};
void GESprite::Do(const GESpriteAction action)
{
	m_nCurrentFrame = action[0];
	m_nCurrentActionPos = 0;
	m_nRepeatActionPos = 0;
	m_pCurrentAction = const_cast<GESpriteAction>(action);
}

void GESprite::Stop()
{
	Do(m_pDefaultAction);	
}

void GESprite::SetDefaultAction(const GESpriteAction action)
{
	m_pDefaultAction = const_cast<GESpriteAction>(action);
}

void GESprite::UpdateFrame()
{
	m_nCurrentFrame = m_pCurrentAction[m_nCurrentActionPos];
	m_nCurrentActionPos++;
	if( m_pCurrentAction[m_nCurrentActionPos] < 0 )
	{
		// Treats function frames
		switch( m_pCurrentAction[m_nCurrentActionPos] )
		{
			case	GE_SPRITE_ACTION_INITREP:
				m_nCurrentActionPos++; // skip current frame
				m_nRepeatActionPos = m_nCurrentActionPos; // set next frame to be the beginning of repeat sequence
				break;
				
			case	GE_SPRITE_ACTION_REPEAT:
				m_nCurrentActionPos = m_nRepeatActionPos;
				break;
				
			case	GE_SPRITE_ACTION_END:
				m_pCurrentAction = m_pDefaultAction; // resets action to default
				m_nCurrentActionPos = 0;
				break;
				
			default:
				break;
		}
	}
}

void GESprite::SetVisible(bool visible)
{
	m_bVisible = visible;
}

bool GESprite::IsVisible()
{
	return m_bVisible;
}

void GESprite::Scale2x()
{
	for(int i = 0; i < m_nTotalFrames; i++)
	{
		m_pFrames[i]->Scale2x();
		m_pFrames[i]->SetColorKey(GE_COLORKEY_R, GE_COLORKEY_G, GE_COLORKEY_B);
	}
	
	m_nWidth *= 2;
	m_nHeight *= 2;
}

void GESprite::SetColorKey(int R, int G, int B)
{
	for(int i = 0; i < m_nTotalFrames; i++)
	{
		m_pFrames[i]->SetColorKey(R, G, B);
	}
}

GESpriteDirection GESprite::GetDirection()
{
	return m_eDirection;
}
