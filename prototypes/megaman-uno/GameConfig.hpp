#ifndef _GAMECONFIG_HPP_
#define	_GAMECONFIG_HPP_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <iostream>
#include <exception>
#include <cassert>

// Comment the line below to remove debug messages
#define DEBUG

#define GAME_NAME				"MegaMan UNO Prototype 2"
#define GAME_FONT_FACE			"tahoma.ttf"
#define	GAME_FONT_SIZE			28

#define	GAME_TEXT_PUSHSTART		"Press ENTER to start."

#define	SCREEN_FRAME_RATE		15

#define	SCREEN_WIDTH			640
#define	SCREEN_HEIGHT			480
#define	SCREEN_BITSPERPIXEL		32
#define	SCREEN_FLAGS			SDL_SWSURFACE | SDL_DOUBLEBUF

#define IMAGE_COLORKEY_R		0x00
#define IMAGE_COLORKEY_G		0xFF
#define IMAGE_COLORKEY_B		0x00

#endif // _GAMECONFIG_HPP_
