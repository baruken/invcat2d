#include "Sprite.hpp"

const int pActionIdle[] = { 0, SPRITE_ACTION_END };

Sprite::Sprite():
m_pFrames(NULL)
{
	#ifdef DEBUG
	std::cout << "Sprite constructor: " << this << std::endl;
	#endif
	
	m_nFrameCount = 0;
}

Sprite::Sprite(const char* file, int width, int height):
m_pFrames(NULL)
{
	#ifdef DEBUG
	std::cout << "Sprite (file) constructor: " << this << std::endl;
	#endif
	
	Image* source_image = NULL;
	source_image = new Image(file);
		
	int nFramesPerRow = source_image->GetWidth() / width;
	int nFramesPerCol = source_image->GetHeight() / height;
	m_nFrameCount = nFramesPerRow * nFramesPerCol;
		
//	m_pFrames = new Image[m_nFrameCount];
	
	SDL_Rect position;
	position.x = 0;
	position.y = 0;
	position.w = width;
	position.h = height;
	
	int nFrame = 0;
	for(int i = 0; i < nFramesPerCol; i++)
	{
		for(int j = 0; j < nFramesPerRow; j++)
		{
			m_vFrames.push_back(Image(source_image, position));
			position.x += width;
		}
		position.x = 0;
		position.y += height;
	}
	
	SetDefaultAction(pActionIdle);
	SetAction(m_pDefaultAction);
	m_eDirection = FACING_RIGHT;
		
	delete source_image;
}

Sprite::~Sprite()
{
	#ifdef DEBUG
	std::cout << "Sprite destructor: " << this << std::endl;
	#endif
	
	delete[] m_pFrames;
}

int Sprite::GetWidth()
{
	return m_pFrames[0].GetWidth();
}

int Sprite::GetHeight()
{
	return m_pFrames[0].GetHeight();
}

SDL_Surface* Sprite::GetCurrentFrame()
{
	if( m_eDirection == FACING_LEFT )
	{
		return m_pFrames[m_nCurrentFrame].GetSurfaceFlip();
	}
	else
	{
		return m_pFrames[m_nCurrentFrame].GetSurface();
	}
}

SDL_Surface* Sprite::GetFrame(int nIndex)
{
	return m_pFrames[nIndex].GetSurface();
}

Image& Sprite::GetImage(int nIndex)
{
	return m_pFrames[nIndex];
}

void Sprite::SetAction(const int* action)
{
	m_nCurrentFrame = action[0];
	m_nCurrentActionPos = 0;
	m_nRepeatActionPos = 0;
	m_pCurrentAction = action;
}

void Sprite::SetDefaultAction(const int* action)
{
	m_pDefaultAction = action;
}

void Sprite::UpdateFrame()
{
	m_nCurrentFrame = m_pCurrentAction[m_nCurrentActionPos];
	m_nCurrentActionPos++;
	
	if( m_pCurrentAction[m_nCurrentActionPos] < 0 )
	{
		// Treats function frames
		switch( m_pCurrentAction[m_nCurrentActionPos] )
		{
			case	SPRITE_ACTION_INITREP:
				m_nCurrentActionPos++; // skip current frame
				m_nRepeatActionPos = m_nCurrentActionPos; // set next frame to be the beginning of repeat sequence
				break;
				
			case	SPRITE_ACTION_REPEAT:
				m_nCurrentActionPos = m_nRepeatActionPos;
				break;
				
			case	SPRITE_ACTION_END:
				m_pCurrentAction = m_pDefaultAction; // resets action to default
				m_nCurrentActionPos = 0;
				break;
				
			default:
				break;
		}
	}
}

void Sprite::SetColorKey(int red, int green, int blue)
{
//	for(int i = 0; i < m_nFrameCount; i++) m_pFrames[i].SetColorKey(red, green, blue);
}

void Sprite::SetPosition(int x, int y)
{
	for(int i = 0; i < m_nFrameCount; i++)
	{
		m_pFrames[i].SetPosition(x, y);
	}
}

SDL_Rect* Sprite::GetPosition()
{
	return m_vFrames[0].GetPosition()
}

Direction Sprite::GetDirection()
{
	return m_eDirection;
}

void Sprite::Scale2x()
{
	for(int i = 0; i < m_nFrameCount; i++) m_vFrames[i].Scale2x();
}
