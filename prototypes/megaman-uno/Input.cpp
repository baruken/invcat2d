#include "Input.hpp"

Input::Input()
{
	#ifdef DEBUG
	std::cout << "Input constructor.\n";
	#endif
	
	m_bKeyStates = SDL_GetKeyState(NULL);
	
	assert( m_bKeyStates != NULL);
}

Input::~Input()
{
	#ifdef DEBUG
	std::cout << "Input destructor.\n";
	#endif
}

bool Input::IsLeft()
{
	return m_bKeyStates[SDLK_LEFT];
}

bool Input::IsRight()
{
	return m_bKeyStates[SDLK_RIGHT];
}

bool Input::IsUp()
{
	return m_bKeyStates[SDLK_UP];
}

bool Input::IsDown()
{
	return m_bKeyStates[SDLK_DOWN];
}

bool Input::IsEnter()
{
	return m_bKeyStates[SDLK_RETURN];
}

bool Input::IsEscape()
{
	return m_bKeyStates[SDLK_ESCAPE];
}
