#include "Game.h"
#include <iostream>
#include "Exception.h"
#include "SDL/SDL.h"
#include "Config.h"

using namespace std;

_Game::_Game():
m_running(false)
{
   //Start SDL
   if( SDL_Init( SDL_INIT_EVERYTHING ) )
   {
      stringstream ss;

      ss << "Unable to initialize SDL. " << SDL_GetError();
      throw Exception("SDL_Error", ss.str(), "(ctor)", "_Game");
   }

   mp_video = new Video();

   SDL_WM_SetCaption(GAME_NAME, NULL);
}

_Game::~_Game()
{
   //Quit SDL
   SDL_Quit();

   delete mp_video;
}

void _Game::Start()
{
   // Initialize subsystems

   // Start game
   m_running = true;
   GameMain();
}

void _Game::Pause()
{

}

void _Game::Resume()
{

}

void _Game::Stop()
{

}

void _Game::GameMain()
{
   SDL_Event event;
   int wait_ticks =  1000 / CONFIG.SCR_FPS();
   uint fps_limit = CONFIG.SCR_FPSLimit();

   while( m_running )
   {
      m_timer.Start();

      while( SDL_PollEvent(&event) )
      {
         switch( event.type )
         {
            case SDL_QUIT:
               m_running = false;
               break;
         }
      }

      mp_video->Update();
      if( fps_limit && (m_timer.GetTicks() < wait_ticks) )
      {
         SDL_Delay(wait_ticks - m_timer.GetTicks());
      }
   }
}
