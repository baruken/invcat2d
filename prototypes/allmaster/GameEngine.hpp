#ifndef _GE_HEADER_
#define _GE_HEADER_

/* GameEngine (GE) Project
 * 
 * File: GameEngine.hpp
 * Created: 2010-05-27
 * Last update: 2010-06-07
 * 
 */

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "GEConstants.hpp"
#include "GEScreen.hpp"
#include "GEInput.hpp"
#include "GETimer.hpp"

class GameEngine
{
	private:
		GameEngine(const GameEngine&);
		GameEngine& operator=(const GameEngine&);
			
	public:
		GameEngine();
		~GameEngine();

		int Start();
		int Pause();
		int Resume();
		int Stop();

	private:
		bool		m_bRunning;
		GEScreen* 	m_pScreen;
		GEInput*	m_pInput;
		// GESound* m_pSound;
};

#endif // GE_HEADER
