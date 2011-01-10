#ifndef __Game_h__
#define __Game_h__

#include "Singleton.h"
#include "Video.h"
#include "Timer.h"

/** Game name. Replace by your own. */
#define GAME_NAME "GE"

/** Internal game representation.
    Should not be used directly.
*/
class _Game
{
   public:
      /** Default constructor.
          This object should never be used directly.
          @see GAME
      */
      _Game();
      ~_Game();

      /** Initialize game rendering. Should be called in main().
          Never call this function directly, use GAME.Start().
      */
      void Start();
      void Pause();
      void Resume();
      void Stop();

   private:
      _Game(const _Game&);
      const _Game& operator=(const _Game&);

      void     GameMain();

      Timer    m_timer;
      Video*   mp_video;
      bool     m_running;
};


/** Game engine main class.
    This class represents an instance of the game. It has multithread capabilities
    to control each of the game subsystems. Also, it's a singleton class.
    Should not be called directly. Instead, use the helper macro GAME.
*/
typedef Singleton<_Game> Game;
/** Simplify the Singleton sintax for calling Game.
    @see _Game
*/
#define GAME (Game::Instance())

#endif // __Game_h__
