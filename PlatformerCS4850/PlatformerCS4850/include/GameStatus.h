#ifndef GAME_STATUS_H
#define GAME_STATUS_H

/** The state of the game. */
enum GameState {
	PLAYING, PAUSED, WON, LOST
};

struct GameStatus {
	
	/** Returns the instance of GameStatus*/
	static GameStatus& instance() {
		if (inst_ == nullptr) {
			inst_ = new GameStatus();
		}
		return *inst_;
	}

	/** Initializes the GameStatus */
	void init(/** The number of hits the player can take */int _health) {
		health = _health;
		state = PLAYING;
	}

	/** The instance of GameStatus */
	static GameStatus* inst_;
	/** The health of the player */
	int health;
	/** The number of frames the player has been invulnerable. -1 means the player is vulnerable */
	int playerInvulnCount = -1;
	/** The current state of the game */
	GameState state;

};

#endif