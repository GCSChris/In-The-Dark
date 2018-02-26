#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <SDL.h>

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

/** Max number of columns supported in level building script. */
const int MAX_COLUMNS = 12;
/** Max number of rows supported in level building script. */
const int MAX_ROWS = 8;


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
