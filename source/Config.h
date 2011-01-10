#ifndef __Config_h__
#define __Config_h__

#include "SDL/SDL.h"
#include "Types.h"
#include "Singleton.h"

// 32 bit color pixel format
#define RGB_ALPHA          0xFF000000
#define RGB_RED            0x00FF0000
#define RGB_GREEN          0x0000FF00
#define RGB_BLUE           0x000000FF

// Recognized parameters
#define CFG_SCR_WIDTH            "width"
#define CFG_SCR_HEIGHT           "height"
#define CFG_SCR_BPP              "bpp"
#define CFG_SCR_FPS              "fps"
#define CFG_SCR_FPS_LIMIT        "fps_limit"
#define CFG_SCR_MODE             "mode"
#define CFG_SCR_MODE_SW          "software"
#define CFG_SCR_MODE_HW          "hardware"
#define CFG_SCR_TRANSMODE        "transmode"
#define CFG_SCR_TRANSMODE_CK     "CK"
#define CFG_SCR_TRANSMODE_PPA    "PPA"
#define CFG_SCR_TRANSMODE_PSA    "PSA"
#define CFG_SCR_TRANSMODE_NONE   "NONE"
#define CFG_RGB_COLORKEY         "colorkey"

// Default values
#define DEFAULT_SCR_WIDTH        800
#define DEFAULT_SCR_HEIGHT       600
#define DEFAULT_SCR_BPP          32
#define DEFAULT_SCR_FPS          15
#define DEFAULT_SCR_FPS_LIMIT    1
#define DEFAULT_SCR_MODE         SDL_SWSURFACE
#define DEFAULT_SCR_TRANSMODE    PPA
#define DEFAULT_SCR_CK_R         0xFF
#define DEFAULT_SCR_CK_G         0x00
#define DEFAULT_SCR_CK_B         0xFF

/** Transparency mode.
    NONE - No transparency
    CK   - Color Keying
    PPA  - Per-Pixel Alpha
    PSA  - Per-Surface Alpha
*/
enum TMode { NONE = 0, CK, PPA, PSA };

/** Internal configuration class.
    Should not be used directly.
    @see Config CONFIG
*/
class _Config
{
   public:
      /** Default constructor.
          This object should never be used directly.
          @see CONFIG
      */
      _Config();
      ~_Config();

      /* Screen properties */
      /** Screen width. */
      inline uint  SCR_Width()    { return m_scr_width; }
      /** Screen height. */
      inline uint  SCR_Height()   { return m_scr_height; }
      /** Screen bits per pixel (color depth). Valid values are 8, 16, 24 and 32. */
      inline uint  SCR_BPP()      { return m_scr_bpp; }
      /** Rendering frame rate in frames per second. */
      inline uint  SCR_FPS()      { return m_scr_fps; }
      /** Whether frame rate limit is on or off. */
      inline uint  SCR_FPSLimit() { return m_scr_fps_limit; }
      /** Rendering mode: hardware or software. */
      inline uint  SCR_Mode()     { return m_scr_mode; }
      /** Transparency mode: per-pixel alpha (PPA), per-surface alpha (PSA) or colorkeying (CK).
          @see TMode
      */
      inline TMode SCR_TMode()    { return m_scr_tmode; }
      /** Returns by-surface formated colorkey. Ensures that the pixel format of the surface is respected. */
      inline uint  SCR_ColorKey(SDL_Surface* s)
      {
         return SDL_MapRGB(s->format, m_scr_ck_r, m_scr_ck_g, m_scr_ck_b);
      }
      /** Returns alpha-channel mask or 0 if disabled. */
      inline uint  RGB_Alpha()    { return (m_scr_tmode == PPA) ? RGB_ALPHA : 0; }

   private:
      _Config(const _Config&);
      const _Config& operator=(const _Config&);

      uint  m_scr_width;
      uint  m_scr_height;
      uint  m_scr_bpp;
      uint  m_scr_fps;
      uint  m_scr_fps_limit;
      uint  m_scr_mode;
      TMode m_scr_tmode;
      uint  m_scr_ck_r;
      uint  m_scr_ck_g;
      uint  m_scr_ck_b;
};
/** Configuration class.
    Holds all configuration data for the application. Implemented as a singleton class.
    Should not be called directly, instead use the CONFIG macro.
    @see CONFIG
*/
typedef Singleton<_Config> Config;

/** Simplify the singleton sintax for recovering config parameters.
    Call 'CONFIG.Function()' where function is the property you need.
    Properties are defined as _Config methods.
    @see _Config
*/
#define CONFIG (Config::Instance())

#endif // __Config_h__
