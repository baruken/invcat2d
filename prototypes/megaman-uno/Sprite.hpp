#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <vector>
#include "GameConfig.hpp"
#include "Image.hpp"

enum ActionControl
{
	SPRITE_ACTION_END		=-1,
	SPRITE_ACTION_REPEAT	=-2,
	SPRITE_ACTION_INITREP	=-3
};

enum Direction
{
	FACING_LEFT,
	FACING_RIGHT
};

class Sprite
{
	public:
		Sprite();
		Sprite(const char* file, int width, int height);
		~Sprite();
		
		void			AddFrame(const Image& frame);
		
		int 			GetWidth();
		int				GetHeight();
		SDL_Surface*	GetCurrentFrame();
		SDL_Surface*	GetFrame(int nIndex);
		Image&			GetImage(int nIndex);
		Direction		GetDirection();
		SDL_Rect*		GetPosition();
		
		void			SetAction(const int* action);
		void			SetDefaultAction(const int* action);
		void			SetColorKey(int red, int green, int blue);
		void			SetPosition(int x, int y);

		void			UpdateFrame();
		
		void			Scale2x();
		
	private:
		std::vector<Image>	m_vFrames;
		int					m_nFrameCount;
		
		int			m_nCurrentFrame;
		int			m_nCurrentActionPos;
		int			m_nRepeatActionPos;
		const int*	m_pDefaultAction;
		const int*	m_pCurrentAction;
		
		Direction	m_eDirection;
};

#endif // _SPRITE_HPP_
