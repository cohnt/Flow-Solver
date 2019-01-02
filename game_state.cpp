#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "game_state.h"

State::StateHelper::StateHelper(size_t cols) : row(cols, Colors::empty) {}

void State::StateHelper::assignRow(std::string line) {
	assert(line.size() == row.size());
	for(size_t i=0; i<line.size(); ++i) {
		if(Colors::charToColor.find(line[i]) != Colors::charToColor.end()) {
			row[i] = static_cast<Colors::ColorsEnum>(Colors::charToColor.at(line[i]));
		}
		else {
			row[i] = Colors::empty;
		}
	}
}

Colors::ColorsEnum& State::StateHelper::operator[](const size_t index) {
	//
	return row[index];
}

const Colors::ColorsEnum& State::StateHelper::operator[](const size_t index) const {
	//
	return row[index];
}

State::State(size_t rows, size_t cols) : board(rows, StateHelper(cols)) {}
State::State(size_t rows, size_t cols, std::vector<std::string> lines) : board(rows, StateHelper(cols)) {
	for(size_t i=0; i<rows; ++i) {
		board[i].assignRow(lines[i]);
	}
}
State::State(std::string fname) : board(0, StateHelper(0)) {
	std::ifstream in(fname.c_str());
	int rows, cols;

	in >> rows;
	in >> cols;

	std::vector<std::string> lines;
	std::string line;
	while(std::getline(in >> std::ws, line)) {
		lines.push_back(line);
	}

	*this = State(rows, cols, lines);

	in.close();
}

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

void State::writeToFile(std::string fname) const {
	std::ofstream out(fname.c_str());

	size_t rows = this->rows();
	size_t cols = this->cols();

	out << rows << ' ' << cols << '\n' << '\n';
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			out << Colors::colorToChar.at((*this)[i][j]);
		}
		out << '\n';
	}

	out.close();
}

size_t State::rows() const {
	//
	return board.size();
}
size_t State::cols() const {
	//
	return board[0].row.size();
}