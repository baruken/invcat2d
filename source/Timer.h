#ifndef __Timer_h__
#define __Timer_h__

/** Basic timer class.
    Used to control the frame rate of animation.
    @see Game::GameMain()
*/

class Timer
{
   public:
      /** Default constructor. */
      Timer();
      /** Default destructor. */
      ~Timer();

      /** Start counting. */
      void  Start();
      /** Stop timer and reset. */
      void  Stop();
      /** Get time difference between start and now.
          Ticks are the same as milliseconds.
      */
      int   GetTicks();

   private:
      int   m_start_ticks;
      bool  m_running;
};

#endif // __Timer_h__
