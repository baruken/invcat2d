#ifndef _GE_TIMER_HEADER_
#define _GE_TIMER_HEADER_

#include "SDL/SDL.h"

class GETimer
{
	public:
		GETimer();
		~GETimer();
		
		void	Start();
		void	Stop();
		void	Pause();
		void	Resume();
		
		int		GetTicks(); // milisseconds
	
	private:
		int		m_nStart;
		int		m_nPaused;
		bool	m_bPaused;
		bool	m_bRunning;
};

#endif // _GE_TIMER_HEADER_
