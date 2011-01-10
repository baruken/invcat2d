#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "GameConfig.hpp"

class Input
{
	public:
		Input();
		~Input();
		
		bool	IsLeft();
		bool	IsRight();
		bool	IsUp();
		bool	IsDown();
		
		bool	IsEnter();
		bool	IsEscape();
	
	private:
		Uint8*	m_bKeyStates;
};

#endif // _INPUT_HPP_
