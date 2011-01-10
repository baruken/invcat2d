#include "Screen.h"
#include "Exception.h"
#include "Config.h"


using namespace std;

Screen::Screen():
Surface()
{
   mp_surface = SDL_SetVideoMode(CONFIG.SCR_Width(), CONFIG.SCR_Height(), CONFIG.SCR_BPP(), CONFIG.SCR_Mode());
   if( !mp_surface )
   {
      stringstream ss;
      ss << "Unable to create screen surface. " << SDL_GetError()
         << " Width: " << CONFIG.SCR_Width()
         << " Height: " << CONFIG.SCR_Height()
         << " BPP: " << CONFIG.SCR_BPP();

      throw Exception(EX_SDL, ss.str(), "(ctor)", "Screen");
   }
}

Screen::~Screen()
{
   // Don't deallocate mp_surface! Will be freed by SDL_Quit
}

void Screen::operator=(Surface& s)
{
   Blit(s);
   SDL_Flip(mp_surface);
}
