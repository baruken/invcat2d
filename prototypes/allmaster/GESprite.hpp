#ifndef _GE_SPRITE_HEADER_
#define _GE_SPRITE_HEADER_

#include <iostream>
#include "SDL/SDL.h"
#include "GEConstants.hpp"
#include "GEImage.hpp"

/* Sprite action script
 * 
 * Use GE_SPRITE_ACTION_END for finite sprite action
 * Use GE_SPRITE_ACTION_REPEAT for infinite (repetitive) sprite action
 * GE_SPRITE_ACTION_INITREP can be used to mark the initial point of 
 * repetitive animation, ie:
 * 
 * ACTION_WALK[] = { 0, 1, 2, GE_SPRITE_ACTION_INITREP, 3, 4, 5, GE_SPRITE_ACTION_REPEAT };
 * */

 class GESprite
 {
	public:
		// Create sprite from sprite map (multiple images)
		GESprite(const char* file, int width, int height);
		~GESprite();
	
		// Properties
		GESpriteDirection	GetDirection();
		int					GetHeight();
		int					GetWidth();
		bool				IsVisible();
		void				SetDefaultAction(const GESpriteAction action);
		void				SetVisible(bool visible);

		// Animation
		void				Do(const GESpriteAction action);
		void				Stop();
		void				UpdateFrame();
		
		SDL_Surface* 		GetCurrentFrame();
		
		// Post-Processing
		void				SetColorKey(int R, int G, int B);
		void				Scale2x();

	protected:
		GESpriteDirection 	m_eDirection;
		int					m_nWidth;
		int					m_nHeight;


	private:
		GESprite();
		void			Init(); // initializes common properties
	
		GEImage*		m_pFrames[GE_SPRITE_MAX_FRAMES];
		int				m_nTotalFrames;
		
		int				m_nCurrentFrame;
		int				m_nCurrentActionPos;
		int				m_nRepeatActionPos;
		GESpriteAction	m_pCurrentAction; // action is a sequence of frames
		GESpriteAction	m_pDefaultAction;
		
		bool			m_bVisible;
};

#endif // _GE_SPRITE_HEADER_
