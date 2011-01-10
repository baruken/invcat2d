/* Config class implementation */

#include "Config.h"
#include <fstream>
#include "StrArray.h"
#include <stdlib.h>

/* Search this file for configuration input */
const char* ps_config_file = "c:\\config.ini";

using namespace std;

_Config::_Config():
m_scr_width(DEFAULT_SCR_WIDTH),
m_scr_height(DEFAULT_SCR_HEIGHT),
m_scr_bpp(DEFAULT_SCR_BPP),
m_scr_fps(DEFAULT_SCR_FPS),
m_scr_fps_limit(DEFAULT_SCR_FPS_LIMIT),
m_scr_mode(DEFAULT_SCR_MODE),
m_scr_tmode(DEFAULT_SCR_TRANSMODE),
m_scr_ck_r(DEFAULT_SCR_CK_R),
m_scr_ck_g(DEFAULT_SCR_CK_G),
m_scr_ck_b(DEFAULT_SCR_CK_B)
{
   ifstream lf_config(ps_config_file);

   if( !lf_config.fail() )
   {
      while( !lf_config.eof() )
      {
         char ls_buffer[MAX_TEXT];

         lf_config.getline(ls_buffer, MAX_TEXT);
         string s(ls_buffer);
         StrArray sa(s, '=');

         if( !sa[0].compare(CFG_SCR_WIDTH) )
         {
            m_scr_width = atoi(sa[1].c_str());
         }
         else if( !sa[0].compare(CFG_SCR_HEIGHT) )
         {
            m_scr_height = atoi(sa[1].c_str());
         }
         else if( !sa[0].compare(CFG_SCR_BPP) )
         {
            m_scr_bpp = atoi(sa[1].c_str());
         }
         else if( !sa[0].compare(CFG_SCR_FPS) )
         {
            m_scr_fps = atoi(sa[1].c_str());
         }
         else if( !sa[0].compare(CFG_SCR_FPS_LIMIT) )
         {
            m_scr_fps_limit = atoi(sa[1].c_str());
         }
         else if( !sa[0].compare(CFG_SCR_MODE) )
         {
            if( !sa[1].compare(CFG_SCR_MODE_SW) )
            {
               m_scr_mode = SDL_SWSURFACE;
            }
            else if( !sa[1].compare(CFG_SCR_MODE_HW) )
            {
               m_scr_mode = SDL_HWSURFACE;
            }
         }
         else if( !sa[0].compare(CFG_SCR_TRANSMODE) )
         {
            if( !sa[1].compare(CFG_SCR_TRANSMODE_NONE) )
            {
               m_scr_tmode = NONE;
            }
            else if( !sa[1].compare(CFG_SCR_TRANSMODE_CK) )
            {
               m_scr_tmode = CK;
            }
            else if( !sa[1].compare(CFG_SCR_TRANSMODE_PPA) )
            {
               m_scr_tmode = PPA;
            }
            else if( !sa[1].compare(CFG_SCR_TRANSMODE_PSA) )
            {
               m_scr_tmode = PSA;
            }
         }
         else if( !sa[0].compare(CFG_RGB_COLORKEY) )
         {
            StrArray sb(sa[1], ',');
            if( sb.Count() == 3 )
            {
               m_scr_ck_r = atoi(sb[0].c_str());
               m_scr_ck_g = atoi(sb[1].c_str());
               m_scr_ck_b = atoi(sb[2].c_str());
            }
         }
      }

      lf_config.close();
   }
}

_Config::~_Config() {}
