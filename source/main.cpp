#include "Config.h"
#include <iostream>
#include "Game.h"

using namespace std;

int main( int argc, char* args[] )
{
   try
   {
      GAME.Start();
   }
   catch(Exception& e)
   {
      cerr << "Abnormal program termination\n"
              "============================\n";
      cerr << "Error       : " << e.Name() << endl;
      cerr << "Description : " << e.Description() << endl;
      cerr << "Scope       : " << e.Class() << "::" << e.Function() << endl;
   }

   return 0;
}

