#ifndef GAME_STATUS_H
#define GAME_STATUS_H

enum GameState {
	PLAYING, PAUSED, WON, LOST
};

struct GameStatus {

	static GameStatus& instance() {
		if (inst_ == nullptr) {
			inst_ = new GameStatus();
		}
		return *inst_;
	}

	void init(int _health) {
		health = _health;
		state = PLAYING;
	}

	static GameStatus* inst_;
	int health;
	int playerInvulnCount = -1;
	GameState state;

};

#endif