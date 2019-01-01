#include "game_state.h"

State::StateHelper::StateHelper(size_t cols) : row(cols, Colors::empty) {}

Colors::ColorsEnum& State::StateHelper::operator[](const size_t index) {
	//
	return row[index];
}

const Colors::ColorsEnum& State::StateHelper::operator[](const size_t index) const {
	//
	return row[index];
}

State::State(size_t rows, size_t cols) : board(rows, StateHelper(cols)) {}

State::StateHelper& State::operator[](const size_t index) {
	//
	return board[index];
}

const State::StateHelper& State::operator[](const size_t index) const {
	//
	return board[index];
}

void State::print() const {
	for(size_t i=0; i<board.size(); ++i) {
		for(size_t j=0; j<(*this)[i].row.size(); ++j) {
			Colors::ColorsEnum color = (*this)[i][j];
			std::cout << Colors::colorToTermCode.at(color) << Colors::colorToChar.at(color) << Colors::reset;
		}
		std::cout << std::endl;
	}
}