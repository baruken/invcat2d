#include "GEPlane.hpp"

GEPlane::GEPlane(Uint32 flags):
m_pPlane(NULL),
m_pPlaneMap(NULL),
m_nSpeed(0),
m_nMapWidth(0),
m_nMapHeight(0),
m_pCollisionManager(NULL)
{
	std::cout << "GEPlane constructor.\n";
	
	SDL_Surface* video = NULL;
	video = SDL_GetVideoSurface();
	
	if (video)
	{
		m_pPlane = SDL_CreateRGBSurface(flags, video->w, video->h, video->format->BitsPerPixel, 
									video->format->Rmask, 
									video->format->Gmask, 
									video->format->Bmask, 
									video->format->Amask);
									
		if( m_pPlane )
		{
			std::cout << "GEPlane constructor: SDL_Surface allocated -> m_pPlane = " << m_pPlane << '\n';
			SDL_SetColorKey(m_pPlane, SDL_SRCCOLORKEY, SDL_MapRGB(video->format, GE_COLORKEY_R, GE_COLORKEY_G, GE_COLORKEY_B));			
			
			m_pCollisionManager = new GECollisionManager();
		}
	}
	
	m_position.x = 0;
	m_position.y = 0;
	m_position.w = video->w; 
	m_position.h = video->h;
	
	// We don't need to free the surface from SDL_GetVideoSurface();
}

GEPlane::~GEPlane()
{
	std::cout << "GEPlane destructor.\n";
	
	if( m_pPlane )
	{
		std::cout << "GEPlane destructor: deallocating SDL_Surface* m_pPlane = " << m_pPlane << '\n';
		delete m_pPlane;
		delete m_pCollisionManager;
	}
}

SDL_Surface* GEPlane::GetSurface()
{
	return m_pPlane;
}

void GEPlane::AddCharacter(GECharacter* pCharacter)
{
	m_pCollisionManager->AddCharacter(pCharacter);
}

void GEPlane::Update()
{
	SDL_Rect draw;
	if( m_pPlaneMap )
	{
		m_position.x += m_pMoveVector->GetFx(); // X displacement
		m_position.y += m_pMoveVector->GetFy(); // Y displacement
		
		draw.x = m_position.x;
		draw.y = m_position.y;
		draw.h = m_position.h; // default 480
		draw.w = m_position.w; // default 640
		
		// Check limits
		if( draw.x < 0 ) draw.x = 0;
		if( draw.x > m_nMapWidth - m_position.w ) draw.x = m_nMapWidth - m_position.w;
		
//		SDL_BlitSurface(m_pCollisionManager->GetCollisionMap(), &draw, m_pPlane, NULL);
		SDL_BlitSurface(m_pPlaneMap->GetSurface(), &draw, m_pPlane, NULL);	
	}
	
	m_pCollisionManager->Update();

	for(int i = 0; i < m_pCollisionManager->GetCharacterCount(); i++)
	{
		GECharacter* pCharacter = m_pCollisionManager->GetCharacter(i);
				
		SDL_Rect* sprite_position = pCharacter->GetPosition();
			
		if( sprite_position->x < 0 ) sprite_position->x = 0;
		if( sprite_position->x > m_nMapWidth ) sprite_position->x = m_nMapWidth;
			
		SDL_Rect sprite_draw;
		sprite_draw.x = sprite_position->x - draw.x;
		sprite_draw.y = sprite_position->y - draw.y;
		sprite_draw.h = sprite_position->h;
		sprite_draw.w = sprite_position->w;
		
		std::cout << "Printing sprite on position " << sprite_draw.x << ":" << sprite_draw.y << "\n";
		
		std::stringstream text;
		
		text << "Coded by: ppetruzalek@yahoo.com.br";
		// debug only
		TTF_Font* font = TTF_OpenFont( "tahoma.ttf", 24 );
		SDL_Color textColor = { 255, 255, 255 }; 
		SDL_Surface* message = TTF_RenderText_Solid( font, text.str().c_str(), textColor );
		SDL_Rect msg_pos;
		msg_pos.x = (GE_SCREEN_WIDTH - message->w) / 2;
		msg_pos.y = (GE_SCREEN_HEIGHT - message->h) - 2;
		msg_pos.w = message->w;
		msg_pos.h = message->h;
		SDL_FillRect(m_pPlane, &msg_pos, SDL_MapRGB( m_pPlane->format, 0, 0, 0) );
		SDL_BlitSurface(message, NULL, m_pPlane, &msg_pos);
		SDL_FreeSurface(message);
		TTF_CloseFont(font);
		
		SDL_BlitSurface(pCharacter->GetCurrentFrame(), NULL, m_pPlane, &sprite_draw);
	}	
}

void GEPlane::SetPlaneMap(GEPlaneMap* plane_map)
{
	m_pPlaneMap = plane_map;
	m_nMapWidth = m_pPlaneMap->GetPixelWidth();
	m_nMapHeight = m_pPlaneMap->GetPixelHeight();	
	m_pCollisionManager->BuildCollisionMap(m_pPlaneMap);
	
}

void GEPlane::SetPlaneSpeed(int speed)
{
	m_nSpeed = speed;
}

void GEPlane::SetMoveVector(GEMoveVector* pMoveVector)
{
	m_pMoveVector = pMoveVector;
}
