#ifndef __MoveVector_h__
#define __MoveVector_h__

enum Direction { DR_NONE = 0, DR_LEFT = -1, DR_RIGHT = 1, DR_UP = -1, DR_DOWN = 1};

struct MoveVector
{
   MoveVector():dir_x(DR_NONE),
                dir_y(DR_NONE),
                vel_x(0),
                vel_y(0) {}

   Direction   dir_x;
   Direction   dir_y;
   double      vel_x;
   double      vel_y;
};

#endif // __MoveVector_h__
