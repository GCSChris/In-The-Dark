#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <SDL.h>

#define FRAMERATE 60

/** The screen width of the game window. */
const int SCREEN_WIDTH = 1280;
/** The screen height of the game window. */
const int SCREEN_HEIGHT = 720;

/** Color constants. */
const SDL_Color COLOR_RED = { 255, 0, 0, 255 }; 
const SDL_Color COLOR_ORANGE = { 255, 165, 0, 255 }; 
const SDL_Color COLOR_BLUE = { 2, 157, 224, 255 };
const SDL_Color COLOR_GREEN = { 144, 168, 23, 255};
const SDL_Color COLOR_MAGENTA = { 142, 4, 96, 255 };
const SDL_Color COLOR_ALPHA = { 0, 255, 0, 255 };

/** Max number of columns supported in level building script. */
const int MAX_COLUMNS = 80;
/** Max number of rows supported in level building script. */
const int MAX_ROWS = 45;
/** The size of a tile in pixels. Pixels are a square */
const int TILE_SIZE = 16;

const int TERMINAL_Y_VELOCITY = 8;
const int GRAVITY = 1;
const int VISIBLE_CIRCLE_MIN_SIZE = 128;

const int PLAYER_WIDTH = 16;
const int PLAYER_HEIGHT = 32;
const int PLAYER_INVULN_FRAME_COUNT = 90;
const int PLAYER_INVULN_FRAME_FLASH_RATE = 15;
const int PLAYER_JUMP_FORCE = 15;
const int PLAYER_RUNNING_SPEED = 3;

const int ENEMY_WIDTH = 48;
const int ENEMY_HEIGHT = 32;
const int ENEMY_RUNNING_SPEED = 2;

// UI CONSTANTS

/** The key to display for the number of lives (from localization file). */
const std::string LIVES_TEXT_STRING = "LIVES";
/** The font style used to display the lives text. */
const std::string LIVES_TEXT_FONT_STYLE = "./resources/arial.ttf";
/** The font size used to display the lives text. */
const int LIVES_TEXT_FONT_SIZE = 16;
/** The text color used to display the lives text. */
const SDL_Color LIVES_TEXT_COLOR = { 255, 255, 255 };


/** The key to display for the current score (from localization file). */
const std::string SCORE_TEXT_STRING = "SCORE";
/** The font style used to display the score text. */
const std::string SCORE_TEXT_FONT_STYLE = "./resources/arial.ttf";
/** The font size used to display the score text. */
const int SCORE_TEXT_FONT_SIZE = 16;
/** The text color used to display the score text. */
const SDL_Color SCORE_TEXT_COLOR = { 255, 255, 255 };

/** The key to display for the paused text (from localization file). */
const std::string PAUSE_TEXT_STRING = "PAUSED";
/** The font style used to display the paused text. */
const std::string PAUSE_TEXT_FONT_STYLE = "./resources/arial.ttf";
/** The font size used to display the paused text. */
const int PAUSE_TEXT_FONT_SIZE = 72;
/** The text color used to display the paused text. */
const SDL_Color PAUSE_TEXT_COLOR = { 255, 255, 255 };

/** The key to display for the loss text (from localization file). */
const std::string LOSS_TEXT_STRING = "YOU LOSE";
/** The font style used to display the loss text. */
const std::string LOSS_TEXT_FONT_STYLE = "./resources/arial.ttf";
/** The font size used to display the loss text. */
const int LOSS_TEXT_FONT_SIZE = 72;
/** The text color used to display the loss text. */
const SDL_Color LOSS_TEXT_COLOR = { 255, 255, 255 };

/** The key to display for the win text (from localization file). */
const std::string WIN_TEXT_STRING = "YOU WIN";
/** The font style used to display the win text. */
const std::string WIN_TEXT_FONT_STYLE = "./resources/arial.ttf";
/** The font size used to display the win text. */
const int WIN_TEXT_FONT_SIZE = 72;
/** The text color used to display the win text. */
const SDL_Color WIN_TEXT_COLOR = { 255, 255, 255 };

#endif
