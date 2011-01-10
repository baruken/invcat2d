 #include "SDL/SDL.h"
 
 int main( int argc, char* argv[])
 {
    // Fire up SDL, this starts all subsystems; audio video etc.
     SDL_Init(SDL_INIT_EVERYTHING);
     // Now Shut it down
     SDL_Quit();
 
     return 0;
 }
st
