#include "Timer.hpp"

Timer::Timer():m_nTicks(0)
{
	#ifdef DEBUG
	std::cout << "Timer constructor: " << this << std::endl;
	#endif
}

Timer::~Timer()
{
	#ifdef DEBUG
	std::cout << "Timer destructor: " << this << std::endl;
	#endif
}

void Timer::Start()
{
	m_nTicks = SDL_GetTicks();
}

int Timer::GetTicks()
{
	return SDL_GetTicks() - m_nTicks;
}
