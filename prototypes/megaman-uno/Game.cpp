#include "Game.hpp"

Game::Game()
{
	#ifdef DEBUG
	std::cout << "Game constructor: " << this << std::endl;
	#endif
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	m_pScreen = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITSPERPIXEL, SCREEN_FLAGS);
	assert( m_pScreen != NULL );
	
	m_pInput = new Input();
	assert( m_pInput != NULL );
	
	TTF_Init();
	
	m_pFont = TTF_OpenFont(GAME_FONT_FACE, GAME_FONT_SIZE);
	assert( m_pFont != NULL );
		
	m_sFontColor.r = 0x00;
	m_sFontColor.g = 0x00;
	m_sFontColor.b = 0x00;
	
	SDL_WM_SetCaption(GAME_NAME, NULL);
	
	m_eGameState = GAME_START;
}

Game::~Game()
{
	#ifdef DEBUG
	std::cout << "Game destructor: " << this << "\n";
	#endif
	
	delete m_pInput;
	delete m_pScreen;
}

void Game::Start()
{
	#ifdef DEBUG
	std::cout << "Game Start()" << std::endl;
	#endif
	
	bool bGameRunning = true;
	
	// Game loop
	while( bGameRunning )
	{
		HandleSystemEvents();
		
		switch( m_eGameState )
		{
			case	GAME_START:
				m_eGameState = Opening();
				break;
				
			case	GAME_TITLE_SCREEN:
				m_eGameState = TitleScreen();
				break;
			
			case	GAME_OPTION_SCREEN:
				m_eGameState = OptionScreen();
				break;
				
			case	GAME_STAGE_SELECT:
				m_eGameState = StageSelect();
				break;
				
			case	GAME_STAGE_OPENING:
				m_eGameState = OpenStage();
				break;
				
			case	GAME_STAGE_PLAYING:
				m_eGameState = PlayStage();
				break;
				
			case	GAME_STAGE_CLOSING:
				m_eGameState = CloseStage();
				break;
				
			case	GAME_ENDING:
				m_eGameState = Ending();
				break;
				
			case	GAME_QUIT:
				bGameRunning = false;
				
			default:
				break;
		}
	}
}

bool Game::HandleSystemEvents()
{
	SDL_Event	event;
	bool		bResult = true;
	
	while( SDL_PollEvent( &event ) )
	{
		switch( event.type )
		{
			case	SDL_QUIT:
				m_eGameState = GAME_QUIT;
				bResult = false;
				break;
		}
	}
	
	return bResult;
}

GameState Game::Opening()
{
	return GAME_TITLE_SCREEN;
}

GameState Game::TitleScreen()
{
	#ifdef DEBUG
	std::cout << "Game TitleScreen()" << std::endl;
	#endif
	
	bool 		bWait = true;
	GameState 	eNextState;

	Image		title_screen("titlescreen.png");
	
	SDL_Surface* 	text = NULL;
	SDL_Surface* 	screen = NULL;
	SDL_Rect		text_position;
	
	text = TTF_RenderText_Solid(m_pFont, GAME_TEXT_PUSHSTART, m_sFontColor);
	text_position.x = (m_pScreen->GetWidth() - text->w) / 2;
	text_position.y = m_pScreen->GetHeight() * 4 / 5;
	
	screen = SDL_DisplayFormat(title_screen.GetSurface());
	SDL_BlitSurface(text, NULL, screen, &text_position);
	
	m_pScreen->FadeIn(screen);

	while( bWait )
	{
		bWait = HandleSystemEvents();
		
		if( m_pInput->IsEscape() )
		{
			bWait = false;
			eNextState = GAME_QUIT;
		}
		
		if( m_pInput->IsEnter() )
		{
			bWait = false;
			eNextState = GAME_STAGE_SELECT;
		}
		
		m_pScreen->Display(screen);
	}
	
	m_pScreen->FadeOut();

	return eNextState;
}

GameState Game::OptionScreen()
{
	return GAME_TITLE_SCREEN;
}

GameState Game::StageSelect()
{
	GameState eResult = GAME_STAGE_SELECT;
	
	Sprite RobotFrames("stageselect_frames.png", 52, 48);
	Sprite RobotFaces("robotmasters_faces.png", 32, 34);
	
	RobotFrames.Scale2x();
	RobotFaces.Scale2x();
	
	SDL_Surface* video = SDL_GetVideoSurface();
	SDL_Rect position;

	int stepx = (video->w - (RobotFrames.GetWidth() * 4)) / 5;
	int stepy = (video->h - (RobotFrames.GetHeight() * 4)) / 5;
	position.x = stepx;
	position.y = stepy;
	
	int framex = (RobotFrames.GetWidth() - RobotFaces.GetWidth()) / 2;
	int framey = (RobotFrames.GetHeight() - RobotFaces.GetHeight()) / 2;
					
	Plane background;
	background.Fill(0x00, 0x95, 0xFF);
	
	RobotFaces.SetPosition(framex, framey);
	
	Sprite BombmanFrame;
	BombmanFrame.AddFrame(RobotFrames.GetImage(0) + RobotFaces.GetImage(0));
	
	int nFrame = 0;
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			SDL_BlitSurface(RobotFrames.GetFrame(0), NULL, background.GetSurface(), &position);
			position.x += RobotFrames.GetWidth() + stepx;
		}
		position.x = stepx;
		position.y += RobotFrames.GetHeight() + stepy;
	}
	
	position.x = stepx + framex;
	position.y = stepy + framey;
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			SDL_BlitSurface(RobotFaces.GetFrame(nFrame++), NULL, background.GetSurface(), &position);
			position.x += RobotFrames.GetWidth() + stepx;
			
			if( nFrame == 6) break;
		}
		position.x = stepx + framex;
		position.y += RobotFrames.GetHeight() + stepy;
		
		if(nFrame == 6) break;
	}
	m_pScreen->Display(background.GetSurface());
	
	SDL_Delay(5000);
	eResult = GAME_QUIT;
	
	/*bool bSelect = true;
	position.x = stepx;
	position.y = stepy;
	
	while( bSelect )
	{
		bSelect = HandleSystemEvents();
		 
		if( m_pInput->IsLeft() )
		{
			SDL_BlitSurface(RobotFrames.GetFrame(0), NULL, background, &position);
			if( position.x == stepx )
			{
				position.x = stepx + 3 * (stepx + RobotFrames.GetWidth());
			}
			else
			{
				position.x -= (stepx + RobotFrames.GetWidth());
			}
			SDL_BlitSurface(RobotFrames.GetFrame(1), NULL, background, &position);
		}
		
		if( m_pInput->IsEscape() )
		{
			eResult = GAME_QUIT;
			bSelect = false;
		}
		
		m_pScreen->Display(background);
	}		*/
	
	return eResult;
}

GameState Game::OpenStage()
{
}

GameState Game::PlayStage()
{
}

GameState Game::CloseStage()
{
}

GameState Game::Ending()
{
}
