#ifndef __Player_h__
#define __Player_h__

#include "Input.h"
#include "Sprite.h"

/** Defines a player character.
    A player character must have a valid input device associated before
    being added to a Plane.
    @see Input Plane
*/
class Player : public Sprite
{
   public:
      /** Default constructor.
          Load player from definition file. This file should also have
          the Sprite definitons.
          @param file Player definition file.
          @see Sprite
      */
      Player(const char* file);
      ~Player();

      /** Blit the Player into the owner Plane.
          Every Player must be assigned to a Plane before being drawed.
          @see GfxObj::SetPlane() Plane
      */
      void  Draw();

      void  Move();

      /** Assign input device to player.
          Should be called before assigning the player to a plane.
      */
      void  SetInput(Input* in);

   private:
      Player();
      Input*   mp_input;
};

#endif // __Player_h__
