#ifndef __Sprite_h__
#define __Sprite_h__

#include "Surface.h"
#include "GfxObj.h"

/** Sprite width. */
#define SPR_WIDTH          "width"
/** Sprite height. */
#define SPR_HEIGHT         "height"

/** Sprite size mode: static or dynamic. */
#define SPR_SIZE           "size"
/** Static sprite size. Use width and height to calculate frame offsets. */
#define SPR_SIZE_STATIC    "static"
/** Dynamic sprite size. Autodetect each frame size from the sprite sheet. Uses width and height as a hint (not required). */
#define SPR_SIZE_DYNAMIC   "dynamic"

/** Default sprite action. If not specified is set as frame zero. */
#define SPR_DEFAULT_ACTION "default"

/** Defines an action. Note: even though 'action' is the keyword, you have to postfix a number to it in order to identify
    the correct action. Example: action1, action2, action3, ..., and so on. */
#define SPR_ACTION         "action"
/** Total number of sprite actions. Should be defined before the 'action' keyword. */
#define SPR_ACTION_NUMBER  "num_acts"
/** Max number of frames per sprite action. Should be defined before the 'action' keyword. */
#define SPR_ACTION_MAX_FR  "actmaxfr"
/** Total number of frames in the sprite sheet.*/
#define SPR_TOTAL_FRAMES   "totalfr"
/** Sprite sheet file. File from which sprite frames are loaded. */
#define SPR_SHEET          "sheet"

/** Sprite action repetition start. */
#define SPR_ACT_REP0       -3
/** Sprite action repetition end. */
#define SPR_ACT_REP1       -2
/** Sprite action end. */
#define SPR_ACT_END        -1

/** Sprite class.
    Handles automatic animations depending on pre-defined action sequences.
    Must always load from a definition file.
    @see GfxObj
*/
class Sprite : public GfxObj
{
   public:
      /** Create a sprite from a file.
          The sprite definition file is a text based file with keywords to describe the sprite.
          It also should point to the sprite sheet (sprite images).
      */
      Sprite(const char* file);
      /** Destructor. */
      ~Sprite();

      /** Start a custom action.
          Actions are defined in the sprite definition file.
      */
      void Do(uint action);
      /** Reset current action to the default action. */
      void Stop();

      /** Plot current sprite surface to the plane.
          Calculate next frame in current action sequence and plot/blit it into the plane surface.
      */
      void  Draw();
      /** Sprite width. */
      uint  Width() { return m_width; }
      /** Sprite height. */
      uint  Height() { return m_height; }

      /** Applies Scale2x filter to all sprite frames. */
      void  Scale2x();

      void  Move();

   private:
      Sprite();
      /** Validate sprite definition file.
          Called by the sprite constructor. There is no need to call it after that.
      */
      void        Validate();

      uint        m_width;
      uint        m_height;
      int         m_num_actions;
      int**       mp_actions;
      int         m_total_frames;
      Surface**   mp_frames;
      Surface**   mp_frames_flip;

      int         m_act_max_fr;
      uint        m_frames;

      int         m_current_frame;
      int         m_act_rep_start;

   protected:
      int         m_current_action;
};

#endif // __Sprite_h__
