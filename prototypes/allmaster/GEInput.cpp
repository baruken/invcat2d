#include "GEInput.hpp"

GEInput::GEInput():
m_bLeft(false), m_bRight(false), m_bUp(false), m_bDown(false),
m_bAction1(false), m_bAction2(false), m_bSelect(false), m_bStart(false)
{
	std::cout << "GEInput constructor.\n";
	m_bKeyStates = SDL_GetKeyState(NULL);
}

GEInput::~GEInput()
{
	std::cout << "GEInput destructor.\n";
}

bool GEInput::IsLeft()
{
	return m_bKeyStates[SDLK_LEFT];
}

bool GEInput::IsRight()
{
	return m_bKeyStates[SDLK_RIGHT];
}

bool GEInput::IsUp()
{
	return m_bKeyStates[SDLK_UP];
}

bool GEInput::IsDown()
{
	return m_bKeyStates[SDLK_DOWN];
}
