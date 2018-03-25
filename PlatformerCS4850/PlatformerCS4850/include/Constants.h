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
/** The maximum speed in the Y direction */
const int TERMINAL_Y_VELOCITY = 8;
/** The force of gravity, applied every frame */
const int GRAVITY = 1;
/** The minimum size of the visibility circle*/
const int VISIBLE_CIRCLE_MIN_SIZE = 128;

/** The width of the player */
const int PLAYER_WIDTH = 16;
/** The height of the player */
const int PLAYER_HEIGHT = 32;
/** The number of invulnerability frames for the player */
const int PLAYER_INVULN_FRAME_COUNT = 90;
/** The number of frames each flash of the sprite takes while invulnerable*/
const int PLAYER_INVULN_FRAME_FLASH_RATE = 15;
/** The force of the player's jump */
const int PLAYER_JUMP_FORCE = 15;
/** The horizontal speed of the player*/
const int PLAYER_RUNNING_SPEED = 3;

/** The width of the enemy */
const int ENEMY_WIDTH = 48;
/** The height of the enemy */
const int ENEMY_HEIGHT = 32;
/** The running speed of the enemy */
const int ENEMY_RUNNING_SPEED = 2;

/** The sprite resources */
const std::string PLAYER_SPRITE = "./resources/PixelTiger_walk.png";
const std::string ENEMY_SPRITE = "./resources/Angry_Wolf.png";
const std::string BATTERY_SPRITE = "./resources/battery.png";
const std::string ROCKET_SPRITE = "./resources/rocket.png";
const std::string TILESET = "./resources/tileset.png";
const std::string VISIBLE_CIRCLE_SPRITE = "./resources/limitedvision.png";

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
