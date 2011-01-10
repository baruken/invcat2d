#include "Sprite.h"
#include <fstream>
#include "StrArray.h"
#include <stdlib.h>
#include "Exception.h"
#include "Plane.h"

#include <iostream>
using namespace std;

Sprite::Sprite(const char* file):
m_width(0), m_height(0), m_num_actions(0),
mp_actions(0), mp_frames(0), mp_frames_flip(0),
m_act_max_fr(0), m_current_frame(0), m_act_rep_start(0),
m_current_action(0)
{
   ifstream sprite(file);
   if( sprite.fail() )
   {
      stringstream ss;
      ss << "File not found: " << file;
      throw Exception(EX_EXTERNAL, ss.str(), "(ctor)", "Sprite");
   }

   string   spr_sheet;

   while( !sprite.eof() )
   {
      char buffer[MAX_TEXT];
      sprite.getline(buffer, MAX_TEXT);
      string s(buffer);
      StrArray sa(s, '=');

      uint pos = 0;
      int action_idx = 0;

      if( !sa[0].compare(SPR_WIDTH) )
      {
         m_width = atoi(sa[1].c_str());
      }
      else if( !sa[0].compare(SPR_HEIGHT) )
      {
         m_height = atoi(sa[1].c_str());
      }
      else if( !sa[0].compare(SPR_ACTION_NUMBER) )
      {
         m_num_actions = atoi(sa[1].c_str());
      }
      else if( !sa[0].compare(SPR_ACTION_MAX_FR) )
      {
         m_act_max_fr = atoi(sa[1].c_str());
      }
      else if( ((pos = sa[0].find(SPR_ACTION)) != string::npos) || !(sa[0].compare(SPR_DEFAULT_ACTION)) )
      {
         if( !mp_actions )
         {
            stringstream ss;
            ss << "'" << SPR_ACTION_NUMBER << "' and '" << SPR_ACTION_MAX_FR << "' are defined before using '"
               << SPR_ACTION << "' keyword.";
            throw Exception(EX_SPRITE_DEF, ss.str(), "(ctor)", "Sprite");
         }

         // If pos = npos, then it's the default action. Nothing to assign.
         if( pos != string::npos )
         {
            string action(SPR_ACTION);
            pos += action.length(); // point to the number

            action_idx = atoi(sa[0].substr(pos).c_str());
         }

         if( action_idx >= m_num_actions )
         {
            stringstream ss;
            ss << SPR_ACTION << action_idx << " out of action bounds (max = "
               << m_num_actions << ", 0 to " << (m_num_actions - 1) << ")";
            throw Exception(EX_SPRITE_DEF, ss.str(), "(ctor)", "Sprite");
         }

         StrArray sb(sa[1], ',');
         if( sb.Count() > m_act_max_fr )
         {
            stringstream ss;
            ss << "Number of action frames for action "
               << action_idx << " higher than '" << SPR_ACTION_MAX_FR
               << "'. Found: " << sb.Count() << " Max: " << m_act_max_fr;
            throw Exception(EX_SPRITE_DEF, ss.str(), "(ctor)", "Sprite");
         }

         // Assign frames to action.
         for(register int i = 0; i < sb.Count(); i++)
         {
            mp_actions[action_idx][i] = atoi(sb[i].c_str());
         }

         // Force sequence termination.
         mp_actions[action_idx][sb.Count()] = SPR_ACT_END;
      }
      else if( !sa[0].compare(SPR_SHEET) )
      {
         spr_sheet = sa[1];
      }
      else if( !sa[0].compare(SPR_TOTAL_FRAMES) )
      {
         m_total_frames = atoi(sa[1].c_str());
      }

      // If both m_actions and m_actmaxfr are defined we
      // are ready to alloc memory for mp_actions.
      if( m_num_actions && m_act_max_fr && !mp_actions)
      {
         mp_actions = new int*[m_num_actions+1];
         for(register int i = 0; i < m_num_actions; i++)
            mp_actions[i] = new int[m_act_max_fr];
      }
   }

   // Validate sprite definition before creating surfaces.
   Validate();

   // Begin loading sprite sheet
   mp_frames = new Surface*[m_total_frames];
   mp_frames_flip = new Surface*[m_total_frames];

   Surface s(spr_sheet.c_str());

   for(register int i = 0; i < m_total_frames; i++)
   {
      s.SetClipRect(0, i*m_width, m_width, m_height);
      mp_frames[i] = new Surface(m_width, m_height);
      mp_frames[i]->Blit(s);
      mp_frames[i]->SetColRef(&m_col);
      mp_frames[i]->SetRowRef(&m_row);

      // Makes flipped image
      mp_frames_flip[i] = new Surface(*mp_frames[i]);
      mp_frames_flip[i]->FlipH();
   }
}

Sprite::~Sprite()
{
   if( mp_actions )
   {
      for(register int i = 0; i < m_num_actions; i++)
         delete[] mp_actions[i];

      delete[] mp_actions;
   }

   if( mp_frames )
   {
      for(register int i = 0; i < m_total_frames; i++)
         delete mp_frames[i];

      delete[] mp_frames;
   }

   if( mp_frames_flip )
   {
      for(register int i = 0; i < m_total_frames; i++)
         delete mp_frames_flip[i];

      delete[] mp_frames_flip;
   }
}

void Sprite::Do(uint action)
{
   if(action < static_cast<uint>(m_num_actions) )
   {
      m_current_action = action;
      m_current_frame = 0; // set first frame of the sequence
      m_act_rep_start = 0; // reset repetition start
   }
}

void Sprite::Draw()
{
   switch( mp_actions[m_current_action][m_current_frame] )
   {
      case SPR_ACT_REP0:
         m_act_rep_start = ++m_current_frame;
         break;

      case SPR_ACT_REP1:
         m_current_frame = m_act_rep_start;
         break;

      case SPR_ACT_END:
         m_current_action = 0; // default
         m_current_frame = 0; // first frame of default action
         break;
   }

   if( m_movevector.dir_x == DR_LEFT )
      mp_plane->Blit(*mp_frames_flip[mp_actions[m_current_action][m_current_frame++]]);
   else
      mp_plane->Blit(*mp_frames[mp_actions[m_current_action][m_current_frame++]]);
}

void Sprite::Validate()
{
   bool invalid = false;
   bool prev_neg;
   int i, j;

   for(i = 0; i < m_num_actions; i++)
   {
      prev_neg = false;
      for(j = 0; j < m_act_max_fr; j++)
      {
         if( mp_actions[i][j] == SPR_ACT_END ) break;
         if( mp_actions[i][j] < 0 )
         {
            if( prev_neg )
            {
               invalid = true;
               break;
            }
            else
               prev_neg = true;
         }
         else
            prev_neg = false;

         // is the frame out of valid range?
         if( mp_actions[i][j] >= m_total_frames )
         {
            stringstream ss;
            ss << SPR_ACTION << i << " frame " << j << " is invalid."
               << "Maximum value is " << m_total_frames - 1 << ".";
            throw Exception(EX_SPRITE_DEF, ss.str(), "Validate()", "Sprite");
         }
      }

      if( invalid ) break;
   }

   if( invalid )
   {
      stringstream ss;
      ss << SPR_ACTION << i << " frame " << j << " is invalid."
         << "Two sucessive negative frames are meaningless.";
      throw Exception(EX_SPRITE_DEF, ss.str(), "Validate()", "Sprite");
   }

   if( !m_height || !m_width )
   {
      stringstream ss;
      ss << "Height or width is zero. "
         << "Height: " << m_height << " Width: " << m_width;
      throw Exception(EX_SPRITE_DEF, ss.str(), "Validate()", "Sprite");
   }
}

void Sprite::Scale2x()
{
   for(register int i = 0; i < m_total_frames; i++)
   {
      mp_frames[i]->Scale2x();
      mp_frames_flip[i]->Scale2x();
   }
}
