#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <iostream>
#include "game_defns.h"

class State {
private:
	class StateHelper {
		friend class State;
	private:
		std::vector<Colors::ColorsEnum> row;

	public:
		StateHelper(size_t cols);
		Colors::ColorsEnum& operator[](const size_t);
		const Colors::ColorsEnum& operator[](const size_t) const;
	};

	std::vector<State::StateHelper> board;

public:
	State(size_t, size_t);
	State::StateHelper& operator[](const size_t);
	const State::StateHelper& operator[](const size_t) const;
	void print() const;
};

#endif