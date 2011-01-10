#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "GameConfig.hpp"
#include "Image.hpp"
#include "Input.hpp"
#include "Screen.hpp"
#include "Sprite.hpp"
#include "Plane.hpp"

enum GameState
{
	GAME_START = 0,
	GAME_TITLE_SCREEN,
	GAME_OPTION_SCREEN,
	GAME_STAGE_SELECT,
	GAME_STAGE_OPENING,
	GAME_STAGE_PLAYING,
	GAME_STAGE_CLOSING,
	GAME_ENDING,
	GAME_QUIT
};

enum GameStage
{
	STAGE_SELECT = 0,
	STAGE_BOMBMAN,
	STAGE_GUTSMAN,
	STAGE_CUTMAN,
	STAGE_ELECMAN,
	STAGE_ICEMAN,
	STAGE_FIREMAN
};

class Game
{
	public:
		Game();
		~Game();
		
		void		Start();
		bool		HandleSystemEvents();
		
		GameState	Opening();
		GameState	TitleScreen();
		GameState	OptionScreen();
		GameState	StageSelect();
		GameState	OpenStage();
		GameState	PlayStage();
		GameState	CloseStage();
		GameState	Ending();
		
	private:
		Input*		m_pInput;
		Screen*		m_pScreen;
		GameState	m_eGameState;
		GameStage	m_eGameStage;
		
		TTF_Font*	m_pFont;
		SDL_Color	m_sFontColor;
};

#endif // _GAME_HPP_
