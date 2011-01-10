#include "GameEngine.hpp"

// Testing
#include "GEPlaneMap.hpp"
#include "GEPlayerCharacter.hpp"

GameEngine::GameEngine():
m_bRunning(false), m_pScreen(NULL), m_pInput(NULL)
{
	std::cout << "GameEngine constructor.\n";
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) != -1 ) 
	{ 
		m_bRunning = true; // if it works set running = true
		std::cout << "SDL_Init succesful.\n";
	}
	else
	{
		std::cout << "SDL_Init failed!\n";
	}
	
	TTF_Init();
	
	m_pScreen = new GEScreen;
}

GameEngine::~GameEngine()
{
	std::cout << "GameEngine destructor.\n";
	delete m_pScreen;
	
	TTF_Quit();
	SDL_Quit();
}

int GameEngine::Start()
{
	std::cout << "GameEngine::Start()\n";
	SDL_WM_SetCaption("Mega Man UNO - Prototype", NULL);
	
	// Random & Test stuff
	int x = 255, y = 0;

	// Prepare system resources
//	GEMoveVector* player_vector = new GEMoveVector();
	GETimer* pTimer = new GETimer;	// Syncronization timer	
	
	// Prepare player character	
	GEPlayerCharacter* player1 = new GEPlayerCharacter("megaman_map.bmp", 32, 32);
	
	player1->Scale2x();
	player1->SetPosition(x, y);
	player1->SetVisible(true);

	// Prepare stage
	GEPlaneMap* planemap = new GEPlaneMap[3];
	planemap[0].LoadPlaneMap("bombman-plane1.map");
	planemap[0].LoadTileSet("bombman-plane1.bmp");
	planemap[0].Scale2x();
	planemap[0].BuildPlane();
	
	planemap[1].LoadPlaneMap("bombman-plane2.map");
	planemap[1].LoadTileSet("bombman-plane2.bmp");
	planemap[1].Scale2x();
	planemap[1].BuildPlane();
	
	planemap[2].LoadPlaneMap("bombman-plane3.map");
	planemap[2].LoadTileSet("bombman-plane3.bmp");
	planemap[2].Scale2x();
	planemap[2].BuildPlane();
		
	// Prepare screen
	m_pScreen->SetMoveVector(player1->GetMoveVector()); // links player movement to the screen
	m_pScreen->SetPlaneMap(1, &planemap[0]);
	m_pScreen->SetPlaneMap(2, &planemap[1]);
	m_pScreen->SetPlaneMap(3, &planemap[2]);
	m_pScreen->AddToPlane(3, player1);
	m_pScreen->Display();
		
	// Others
	SDL_Event	event;
	bool		bRunOnce = true;
	
	while( m_bRunning ) 
	{
		pTimer->Start();
		
/*		if( bRunOnce )
		{
			if( player4->GetPosition()->y < 300 )
			{
				player4->TeleportIn();
				player4->Lock(); // TODO: Move lock() logic to player character!
			}
			else
			{
				player4->Unlock();
				player4->TeleportLand();
				bRunOnce = false;
			}
		}
*/		
		while( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case	SDL_QUIT:
					m_bRunning = false;
					break;
			}
		}
		
		m_pScreen->Display();
		
		// Limit frame rate to GE_FRAME_RATE
		if( pTimer->GetTicks() < (1000 / GE_FRAME_RATE) )
		{
			SDL_Delay( (1000 / GE_FRAME_RATE) - pTimer->GetTicks() );	
		}
	}
	
	delete[] planemap;
	delete m_pInput;
	delete player1;
	delete pTimer;
	
	return 1;
}
