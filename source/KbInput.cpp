#include "KbInput.h"

KbInput::KbInput()
{
   mp_keystates = SDL_GetKeyState(NULL);
   // TODO: load keys from file
   m_up = SDLK_UP;
   m_down = SDLK_DOWN;
   m_left = SDLK_LEFT;
   m_right = SDLK_RIGHT;
   m_escape = SDLK_ESCAPE;
   m_enter = SDLK_RETURN;
   m_pause = SDLK_PAUSE;
   m_select = SDLK_TAB;

   m_num_actions = 4;
   mp_actions = new int[m_num_actions];
   mp_actions[0] = SDLK_z;
   mp_actions[1] = SDLK_x;
   mp_actions[2] = SDLK_c;
   mp_actions[3] = SDLK_v;
}

KbInput::~KbInput()
{
   delete[] mp_actions;
}

bool KbInput::Up()      { return mp_keystates[m_up]; }
bool KbInput::Down()    { return mp_keystates[m_down]; }
bool KbInput::Left()    { return mp_keystates[m_left]; }
bool KbInput::Right()   { return mp_keystates[m_right]; }
bool KbInput::Escape()  { return mp_keystates[m_escape]; }
bool KbInput::Enter()   { return mp_keystates[m_enter]; }
bool KbInput::Pause()   { return mp_keystates[m_pause]; }
bool KbInput::Select()  { return mp_keystates[m_select]; }

bool KbInput::Action(uint action)
{
   return mp_keystates[mp_actions[action]];
}
