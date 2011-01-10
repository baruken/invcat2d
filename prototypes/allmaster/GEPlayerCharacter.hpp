#ifndef _GE_PLAYERCHARArCTER_HEADER_
#define	_GE_PLAYERCHARACTER_HEADER_

#include <iostream>
#include "GECharacter.hpp"
#include "GEInput.hpp"

/* PlayerCharacter mechanics:
 * 
 * PC has a input device that is not an AI.
 * This device is currently being set as the keyboard by default.
 * The complete implementation should have an option to map other devices.
 * 
 * The PC must define it's Character actions (sprite sequences) and
 * parameters in the constructor.
 * 
 * To enable the PC one must create it and associate with a plane.
 * 
 * The Update() function overrides the virtual function from GECharacter
 * and should handle all the input from the player, calling the corresponding
 * methods from GECharacter.
 *  
 * */

const int teleport[] = { 0, GE_SPRITE_ACTION_REPEAT };
const int teleport_out[] = { 3, 2, 1, GE_SPRITE_ACTION_INITREP, 0, GE_SPRITE_ACTION_REPEAT };
const int teleport_land[] = { 1, 2, 3, GE_SPRITE_ACTION_END };

const int stand[] = { 3, GE_SPRITE_ACTION_REPEAT };
const int walk[] = { 4, GE_SPRITE_ACTION_INITREP,5, 6, 7, 6, GE_SPRITE_ACTION_REPEAT };
const int jump[] = {10, GE_SPRITE_ACTION_REPEAT };

class GEPlayerCharacter: public GECharacter
{
	public:
		GEPlayerCharacter(const char* file, int width, int height);
		~GEPlayerCharacter();
	
		void	UpdateInput();

	private:
		GEInput* m_pInput;
};

#endif // _GE_PLAYERCHARACTER_HEADER_
