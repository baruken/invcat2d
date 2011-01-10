#ifndef _GE_INPUT_HEADER_
#define _GE_INPUT_HEADER_

/*
 * Input handler. 
 * Should be associated to a move vector to be able to process player input
 */

#include <iostream>
#include "SDL/SDL.h"

/* TODO: KeyMap class to customize input
class GEKeyMap
{
	public:
		GEKeyMap();
		~GEKeyMap(); 
		
	private:
}
*/

class GEInput
{
	public:
		GEInput();
		~GEInput();
		
//		void	SetKeyMap(GEKeyMap* pKeyMap);
	
		bool	IsLeft();
		bool	IsRight();
		bool	IsUp();
		bool	IsDown();
		bool	IsAction1();
		bool	IsAction2();
		bool	IsSelect();
		bool	IsStart();
	
		void	Update();

	private:
		bool	m_bLeft;
		bool	m_bRight;
		bool	m_bUp;
		bool	m_bDown;
		bool	m_bAction1;
		bool	m_bAction2;
		bool	m_bSelect;
		bool	m_bStart;
	
		Uint8*	m_bKeyStates;
//		GEKeyMap	m_pKeyMap;
};
 
#endif // _GE_INPUT_HEADER_
 
