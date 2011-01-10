#include "Player.h"
#include "Exception.h"

Player::Player(const char* file):
Sprite(file), mp_input(0)
{

}

Player::~Player()
{
   if( mp_input ) delete mp_input;
}

void Player::Draw()
{
   if( !mp_input )
   {
      stringstream ss;
      ss << "Invalid input device.";
      throw Exception(EX_INTERNAL, ss.str(), "Draw()", "Player");
   }

   Move();
   Sprite::Draw();
}

void Player::Move()
{
   bool left = mp_input->Left();
   bool right = mp_input->Right();
   bool up = mp_input->Up();
   bool down = mp_input->Down();

   bool move_x = left | right;
   bool move_y = up | down;

//   m_movevector.dir_y = m_movevector.dir_x = DR_NONE;
   m_movevector.vel_x = 0;
   m_movevector.vel_y = 0;

   if( !move_x )
   {
      if( m_current_action != 0 ) Do(0);
   }
   else
   {
      if( left )
      {
         m_movevector.dir_x = DR_LEFT;
         m_movevector.vel_x = 4;
      }
      if( right )
      {
         m_movevector.dir_x = DR_RIGHT;
         m_movevector.vel_x = 4;
      }
      if( m_current_action != 1 )
      {
         m_movevector.vel_x = 2;
         Do(1);
      }
   }

   if( move_y )
   {
      if( down )
      {
         m_movevector.dir_y = DR_DOWN;
         m_movevector.vel_y = 2;
      }
      if( up )
      {
         m_movevector.dir_y = DR_UP;
         m_movevector.vel_y = 2;
      }
      if( m_current_action != 2 ) Do(2);
   }

   m_row += (m_movevector.dir_y * m_movevector.vel_y);
   m_col += (m_movevector.dir_x * m_movevector.vel_x);
}

void Player::SetInput(Input* in)
{
   if( mp_input ) delete mp_input;
   mp_input = in;
}
