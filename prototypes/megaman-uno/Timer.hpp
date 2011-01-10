#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include "GameConfig.hpp"

class Timer
{
	public:
		Timer();
		~Timer();
		
		void 	Start();
		
		int		GetTicks();
		
	private:
		int		m_nTicks;
};

#endif // _TIMER_HPP_
