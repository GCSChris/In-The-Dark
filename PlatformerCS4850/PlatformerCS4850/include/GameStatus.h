#ifndef GAME_STATUS_H
#define GAME_STATUS_H

/** A GameStatus Struct */
struct GameStatus {

	/** Initializes GameStatus with the given amount of lives and score */
	void init(/** The amount of lives */ int _lives, /** The score */ int _score) {
		lives = _lives;
		score = _score;
		isPaused = false;
		gameOver = false;
		gameWon = false;

		ballFrozenCount = 0;
	}

	/** The current life count */
	int lives;
	/** The current score */
	int score;

	/** Whether or not the game is paused */
	bool isPaused;
	/** Whether or not the game is over */
	bool gameOver;
	/** Whether or not the game is won*/
	bool gameWon;

	/** Represents the number of frames ball has been frozen */
	int ballFrozenCount;
};

#endif