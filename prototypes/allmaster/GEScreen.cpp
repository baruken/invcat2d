#include "GEScreen.hpp"

GEScreen::GEScreen():m_pScreen(NULL)
{
	std::cout << "GEScreen constructor.\n";
	
	m_pScreen = SDL_SetVideoMode(GE_SCREEN_WIDTH, GE_SCREEN_HEIGHT, GE_SCREEN_BPP, GE_SCREEN_FLAGS); 
	
	if( m_pScreen )
	{
		std::cout << "Screen surface allocated correctly. Proceding to planes...\n";
		
		for(int i = 0; i < GE_SCREEN_MAX_PLANES; i++)
		{
			// Create all game planes. By default the plane 0 is drawed first, so it should be the background.
			// The plane 2 or 3 should be used to the player since they are on the front of the screen.
			m_pPlanes[i] = new GEPlane(SDL_SWSURFACE);
			m_pPlanes[i]->SetPlaneSpeed(i);
		}
	}
	else
	{
		std::cout << "Failed allocating screen surface!\n";
	}
	
}

GEScreen::~GEScreen()
{
	std::cout << "GEScreen destructor.\n";
	
	if( m_pScreen ) // SDL_Quit will deallocate screen;
	{
		std::cout << "Deleting planes...\n";
		for(int i = 0; i < GE_SCREEN_MAX_PLANES; i++)
		{
			delete m_pPlanes[i];
		}
	}
}

void GEScreen::Display()
{
	for(int i = 0; i < GE_SCREEN_MAX_PLANES; i++)
	{
		m_pPlanes[i]->Update();
		SDL_BlitSurface(m_pPlanes[i]->GetSurface(), NULL, m_pScreen, NULL); // Makes the composite image from all planes
	}
	
	SDL_Flip(m_pScreen); // Updates the screen
}

void GEScreen::AddToPlane(int nPlane, GECharacter* pCharacter)
{
	std::cout << "Character " << pCharacter << " added to Plane " << nPlane << "\n";
	m_pPlanes[nPlane]->AddCharacter(pCharacter);
}

void GEScreen::SetPlaneMap(int nPlane, GEPlaneMap* plane_map)
{
	std::cout << "PlaneMap " << plane_map << " assigned to plane " << nPlane << "\n";
	m_pPlanes[nPlane]->SetPlaneMap(plane_map);
}

void GEScreen::SetMoveVector(GEMoveVector* move_vector)
{
	std::cout << "MoveVector " << move_vector << " associated with all planes.\n";
	for(int i = 0; i < GE_SCREEN_MAX_PLANES; i++)
	{
		m_pPlanes[i]->SetMoveVector(move_vector);
	}
}
