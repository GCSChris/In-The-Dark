#ifndef PLAYER_STATUS_H
#define PLAYER_STATUS_H

struct PlayerStatus {

	void init(int _lives, int _score) {
		lives = _lives;
		score = _score;
		isPaused = false;
		gameOver = false;
		gameWon = false;

		ballFrozenCount = 0;
	}

	int lives;
	int score;

	bool isPaused;
	bool gameOver;
	bool gameWon;

	int ballFrozenCount;
};

#endif