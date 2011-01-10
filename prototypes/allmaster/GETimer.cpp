#include "GETimer.hpp"

GETimer::GETimer():m_nStart(0), m_nPaused(0), m_bRunning(false), m_bPaused(false)
{
}

GETimer::~GETimer()
{
}

int GETimer::GetTicks()
{
	int ticks = 0;
	
	if( m_bRunning )
	{
		if( !m_bPaused )
		{
			ticks = SDL_GetTicks() - m_nStart;
		}
		else
		{
			ticks = m_nPaused - m_nStart;
		}
	}
		
	return ticks;
}

void GETimer::Start()
{
	m_bRunning = true;
	m_nStart = SDL_GetTicks();
}

void GETimer::Stop()
{
	m_bRunning = false;
	m_bPaused = false;
}

void GETimer::Pause()
{
	if( m_bRunning && !m_bPaused )
	{
		m_bPaused = true;
		m_nPaused = SDL_GetTicks() - m_nStart;
	}
}

void GETimer::Resume()
{
	if( m_bRunning && m_bPaused )
	{
		m_bPaused = false;
		m_nStart = SDL_GetTicks() - m_nPaused;
		m_nPaused = 0;
	}
}
