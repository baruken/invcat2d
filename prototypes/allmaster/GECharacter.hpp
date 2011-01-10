#ifndef _GE_CHARACTER_HEADER_
#define	_GE_CHARACTER_HEADER_

#include "GEConstants.hpp"
#include "GESprite.hpp"
#include "GEMoveVector.hpp"


class GECharacter: public GESprite
{
	public:
		GECharacter(const char* file, int width, int height);
		~GECharacter();
		
		GECollisionType 	GetCollisionType();
		int					GetHitPoints();
		GEMoveVector*		GetMoveVector();
		SDL_Rect*			GetPosition();
		
		void			SetAction(GEAction eActionType, const GESpriteAction action);
		void			SetCollisionType(GECollisionType eCollisionType);
		void			SetHitPoints(int nHitPoints);
		void			SetPosition(int x, int y);
		void			SetMoveVector(GEMoveVector* pMoveVector);

		virtual void	UpdateInput() = 0;
		
		// Actions
		void			MoveLeft();
		void			MoveRight();
		void			Jump();
		void			Dash();
		
		// Status Control
		void			Stand(); 		// as oppose of move
		void			CancelJump(); 	// as oppose of jump
		void			Land();
		void			Fall();
		
		// Status
		bool			IsFalling();
		
		// Post-processing
		void			Scale2x();

	private:
		// Game Mechanics
		GECollisionType	m_eCollisionType;
		SDL_Rect		m_Position;
		GEMoveVector*	m_pMoveVector;
		bool			m_bOnGround;
		
	protected:
		int				m_nCurrentAction;
		
		// Character Stats
		int		m_nHitPoints;
		int		m_nJumpHeight; // A counter for current jump

		// Parameters for movement
		int		m_nShortStep;
		int		m_nLongStep;
		int		m_nVerticalStep;
		int		m_nTeleportStep;
		int		m_nJumpMaxHeight;		

	private:
		//	Actions
		GESpriteAction	m_pStand;
		GESpriteAction	m_pMove;
		GESpriteAction	m_pJump;
		GESpriteAction	m_pDash;
		GESpriteAction	m_pAttack;
		GESpriteAction	m_pTeleportIn;
		GESpriteAction	m_pTeleportLand;
		GESpriteAction	m_pTeleportOut;
};

#endif

/*
 * 		// Player Actions
		void	Attack();
		void	TeleportIn();
		void	TeleportLand();
		void	TeleportOut();
		
		// Action cancelation (on button release)
		void	CancelJump();
		void	CancelDash();

		// Player events
		void	Hit();  // Enemy or object
		void	Land(); // After a jump
		void	Fall(); // From edges -> It's not a jump!
		
	private:
		bool	m_bOnGround; // true = on ground, false = on air (jumping/falling)
 * */
