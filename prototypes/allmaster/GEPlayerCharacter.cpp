#include "GEPlayerCharacter.hpp"

GEPlayerCharacter::GEPlayerCharacter(const char* file, int width, int height):
GECharacter(file, width, height)
{
	m_pInput = new GEInput();
	
	SetDefaultAction(stand);
	SetAction(GE_ACTION_STANDING, stand);
	SetAction(GE_ACTION_MOVING_RIGHT, walk);
	SetAction(GE_ACTION_MOVING_LEFT, walk);
	SetAction(GE_ACTION_JUMPING, jump);
	SetAction(GE_ACTION_TELEPORT_IN, teleport);
	SetAction(GE_ACTION_TELEPORT_LAND, teleport_land);
	SetAction(GE_ACTION_TELEPORT_OUT, teleport_out);
	
	m_nShortStep = 1;
	m_nLongStep = 8;
	m_nTeleportStep = 32;
	m_nVerticalStep = 16;
	m_nJumpHeight = 0;
	m_nJumpMaxHeight = 3;
	
	m_nCurrentAction = GE_ACTION_STANDING;
}

GEPlayerCharacter::~GEPlayerCharacter()
{
	delete m_pInput;
}

void GEPlayerCharacter::UpdateInput()
{
	if( m_pInput->IsLeft() || m_pInput->IsRight() )
	{
		if( m_pInput->IsLeft() && m_pInput->IsRight() )
		{
			// Both at same time = stand!
			Stand();
		}
		else if( m_pInput->IsLeft() )
		{
			MoveLeft();
		}
		else // if( m_pInput->IsRight() )
		{
			MoveRight();
		}
	}
	else // no direction button pressed
	{
		Stand();
	}
	
	if( m_pInput->IsUp() )
	{
		Jump();
	}
	else
	{
		// If was jumping cancel, else do nothing
		CancelJump();
	}
}
