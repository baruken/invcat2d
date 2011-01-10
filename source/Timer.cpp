#include "Timer.h"
#include "SDL/SDL.h"

Timer::Timer():
m_start_ticks(0),
m_running(false)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
   m_running = true;
   m_start_ticks = SDL_GetTicks();
}

void Timer::Stop()
{
   m_running = false;
   m_start_ticks = 0;
}

int Timer::GetTicks()
{
   if( m_running )
      return SDL_GetTicks() - m_start_ticks;
   else
      return 0;
}
