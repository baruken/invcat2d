#include "GECharacter.hpp"

GECharacter::GECharacter(const char* file, int width, int height):
GESprite(file, width, height), m_bOnGround(false),
m_nShortStep(0), m_nLongStep(0), m_nVerticalStep(0), m_nTeleportStep(0), m_nJumpMaxHeight(0)
{
	std::cout << "GECharacter constructor.\n";
	m_Position.x = 0;
	m_Position.y = 0;
	m_Position.w = m_nWidth; 	// From GESprite
	m_Position.h = m_nHeight;	
	
	m_pMoveVector = new GEMoveVector();
}

GECharacter::~GECharacter()
{
	std::cout << "GECharacter destructor.\n";
	delete m_pMoveVector;
}

SDL_Rect* GECharacter::GetPosition()
{
	return &m_Position;
}

void GECharacter::SetPosition(int x, int y)
{
	m_Position.x = x;
	m_Position.y = y;
}

GEMoveVector* GECharacter::GetMoveVector()
{
	return m_pMoveVector;
}

void GECharacter::SetAction(GEAction eActionType, const GESpriteAction action)
{
	switch(eActionType)
	{
		case GE_ACTION_ATTACKING:
			m_pAttack = const_cast<GESpriteAction>(action);
			break;
			
		case GE_ACTION_DASHING:
			m_pDash = const_cast<GESpriteAction>(action);
			break;
			
		case GE_ACTION_JUMPING:
			m_pJump = const_cast<GESpriteAction>(action);
			break;
			
		case GE_ACTION_MOVING_LEFT:
		case GE_ACTION_MOVING_RIGHT:
			m_pMove = const_cast<GESpriteAction>(action);
			break;
			
		case GE_ACTION_STANDING:
			m_pStand = const_cast<GESpriteAction>(action);
			break;
		
		case GE_ACTION_TELEPORT_IN:
			m_pTeleportIn = const_cast<GESpriteAction>(action);
			break;
			
		case GE_ACTION_TELEPORT_LAND:
			m_pTeleportLand = const_cast<GESpriteAction>(action);
			break;
			
		case GE_ACTION_TELEPORT_OUT:
			m_pTeleportOut = const_cast<GESpriteAction>(action);
			break;
			
		default:
			break;
	}
}

void GECharacter::Stand()
{
	if( m_bOnGround )
	{
		Do(m_pStand);
		m_nCurrentAction = GE_ACTION_STANDING;
	}
	
	m_pMoveVector->SetFx(0);
}

void GECharacter::MoveLeft()
{
	if( m_nCurrentAction & GE_ACTION_MOVING_LEFT )
	{
		// Already moving left, just update position
		m_Position.x -= m_nLongStep;
		m_pMoveVector->SetFx(-m_nLongStep);
	}
	else
	{
		// Was moving right or standing
		// if( m_direction == GE_SPRITE_FACING_RIGHT )
		m_eDirection = GE_SPRITE_FACING_LEFT;
		
		m_nCurrentAction |= GE_ACTION_MOVING_LEFT;
		m_nCurrentAction &= ~GE_ACTION_MOVING_RIGHT;
				
		if( m_bOnGround ) Do(m_pMove); // m_pMoveLeft

		m_Position.x -= m_nShortStep;
		m_pMoveVector->SetFx(-m_nShortStep);
	}
}

void GECharacter::MoveRight()
{
	if( m_nCurrentAction & GE_ACTION_MOVING_RIGHT )
	{
		// Already moving right, just update position
		m_Position.x += m_nLongStep;
		m_pMoveVector->SetFx(m_nLongStep);
	}
	else
	{
		// Was moving left or standing
		// if( m_direction == GE_SPRITE_FACING_LEFT )
		m_eDirection = GE_SPRITE_FACING_RIGHT;
		
		m_nCurrentAction |= GE_ACTION_MOVING_RIGHT;
		m_nCurrentAction &= ~GE_ACTION_MOVING_LEFT;
				
		if( m_bOnGround ) Do(m_pMove); // m_pMoveRight

		m_Position.x += m_nShortStep;
		m_pMoveVector->SetFx(m_nShortStep);
	}
}

void GECharacter::Jump()
{
	if( m_nCurrentAction & GE_ACTION_FALLING )
	{
		// was falling? can't jump while falling!		
	}
	else
	{ // no, was not...
		if( m_nCurrentAction & GE_ACTION_JUMPING )
		{
			// Already Jumping - keep going
			if( m_nJumpHeight < m_nJumpMaxHeight )
			{
				m_Position.y -= m_nVerticalStep;
				m_nJumpHeight++;
			}
			else
			{	// Hit max height - starts to fall
				CancelJump();
			}
		}
		else
		{	// Was not jumping neither falling
			m_nCurrentAction |= GE_ACTION_JUMPING;
			m_bOnGround = false;
			m_Position.y -= m_nVerticalStep;
			m_nJumpHeight = 1;
			Do(m_pJump);
		}
	}
}

void GECharacter::CancelJump()
{
	m_nCurrentAction &= ~GE_ACTION_JUMPING;
}

void GECharacter::Fall()
{
	if( m_nCurrentAction & GE_ACTION_JUMPING )
	{
		// Cannot fall while jumping
	}
	else
	{
		if( m_nCurrentAction & GE_ACTION_FALLING )
		{
			// Already falling
			m_nJumpHeight--;
			m_Position.y += m_nVerticalStep;
		}
		else
		{
			// Start falling
			m_nCurrentAction &= ~GE_ACTION_JUMPING; // Can't fall and jump at same time!
			m_nCurrentAction |= GE_ACTION_FALLING;
			Do(m_pJump); // jump sprite is the same as the falling one
			m_bOnGround = false;
		}
	}
}

void GECharacter::Land()
{
	// Was on air? if not do nothing!
	if( !m_bOnGround )
	{
		if( m_nCurrentAction & (GE_ACTION_MOVING_LEFT | GE_ACTION_MOVING_RIGHT) )
		{
			// Moving while in air, keep moving on land
			Do(m_pMove);
		}
	/*	else if( m_nCurrentAction & GE_ACTION_TELEPORT_LAND )
		{
			Do(m_pTeleportLand);
			m_nCurrentAction = GE_ACTION_STANDING;
		}*/
		else
		{	// landed still (not moving)
			Do(m_pStand);
		}
	
		m_pMoveVector->SetFy(0);
	
		// Cancel falling status (you only can land afer a fall)
		m_nCurrentAction &= ~GE_ACTION_FALLING;
		m_nJumpHeight = 0; // sets new ground level
		m_bOnGround = true;
	}
}

void GECharacter::Scale2x()
{
	m_nShortStep *= 2;
	m_nLongStep *= 2;
	m_nTeleportStep *= 2;
	m_nVerticalStep *= 2;
	
	m_Position.w *=2;
	m_Position.h *=2; // f***ing bug!!! TODO: enhance Scale2x logic -> move all properties to GEImage
	
	GESprite::Scale2x();
}

/*
void GEPlayerCharacter::TeleportIn()
{
	if( m_nCurrentAction & GE_ACTION_TELEPORT_IN )
	{
		m_pPosition->y += m_nTeleportStep;
	}
	else
	{
		m_pPosition->y = 0;
		m_nCurrentAction = GE_ACTION_TELEPORT_IN;
		Do(m_pTeleportIn);
	}
}

void GEPlayerCharacter::TeleportLand()
{
	m_nCurrentAction = GE_ACTION_TELEPORT_LAND;
	Land();
}




void GEPlayerCharacter::Dash()
{
}

void GEPlayerCharacter::Attack()
{
}

void GEPlayerCharacter::Update()
{

}

*/

bool GECharacter::IsFalling()
{
	return m_nCurrentAction & GE_ACTION_FALLING;
}
