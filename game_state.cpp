#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "game_state.h"

void State::makeEmptyBoard(size_t rows_in, size_t cols_in) {
	//Delete the old board if it exists
	if(board != nullptr) {
		deleteBoard();
	}

	//Create the new board, with every square set to empty
	board = new Colors::ColorsEnum*[rows];
	for(size_t i=0; i<rows; ++i) {
		board[i] = new Colors::ColorsEnum[cols_in];
		for(size_t j=0; j<cols_in; ++j) {
			board[i][j] = Colors::empty;
		}
	}
}
void State::deleteBoard() {
	for(size_t i=0; i<rows; ++i) {
			delete[] board[i];
		}
	delete[] board;
	board = nullptr;
}

State::State(size_t rows_in, size_t cols_in) : rows(rows_in), cols(cols_in), board(nullptr) {
	//
	makeEmptyBoard(rows, cols);
}
State::State(size_t rows_in, size_t cols_in, std::vector<std::string> lines) : rows(rows_in), cols(cols_in), board(nullptr) {
	makeEmptyBoard(rows, cols);

	//Transfer data over from lines to board
	assert(lines.size() == rows);
	for(size_t i=0; i<rows; ++i) {
		assert(lines[i].size() == cols);
		for(size_t j=0; j<cols; ++j) {
			if(Colors::charToColor.find(lines[i][j]) != Colors::charToColor.end()) {
				board[i][j] = static_cast<Colors::ColorsEnum>(Colors::charToColor.at(lines[i][j]));
			}
			else {
				board[i][j] = Colors::empty;
			}
		}
	}
}
State::State(const std::string & fname) : rows(0), cols(0), board(nullptr) {
	std::ifstream in(fname.c_str());

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

State::~State() {
	//
	deleteBoard();
}
State::State(const State & other) : rows(other.getRows()), cols(other.getCols()), board(nullptr) {
	makeEmptyBoard(rows, cols);
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			board[i][j] = other[i][j];
		}
	}
}
State & State::operator=(const State & other) {
	if(this != &other) {
		rows = other.getRows();
		cols = other.getCols();

		makeEmptyBoard(rows, cols);
		for(size_t i=0; i<rows; ++i) {
			for(size_t j=0; j<cols; ++j) {
				board[i][j] = other[i][j];
			}
		}
	}
	return *this;
}

size_t State::getRows() const {
	//
	return rows;
}
size_t State::getCols() const {
	//
	return cols;
}
size_t State::numEmpty() const {
	size_t total = 0;
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			total += (board[i][j] == Colors::empty);
		}
	}
	return total;
}

void State::print() const {
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			Colors::ColorsEnum color = board[i][j];
			std::cout << Colors::colorToTermCode.at(color) << Colors::colorToChar.at(color) << Colors::reset;
		}
		std::cout << std::endl;
	}
}
void State::writeToFile(const std::string & fname) const {
	std::ofstream out(fname.c_str());

	out << rows << ' ' << cols << '\n' << '\n';
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			out << Colors::colorToChar.at(board[i][j]);
		}
		out << '\n';
	}

	out.close();
}

Colors::ColorsEnum & State::at(size_t row, size_t col) {
	Colors::ColorsEnum & foo = board[row][col];
	return foo;
}
const Colors::ColorsEnum & State::at(size_t row, size_t col) const {
	const Colors::ColorsEnum & foo = board[row][col];
	return foo;
}

Colors::ColorsEnum* State::operator[](const size_t row) {
	Colors::ColorsEnum* bar = board[row];
	return bar;
}
Colors::ColorsEnum* const State::operator[](const size_t row) const {
	Colors::ColorsEnum* const bar = board[row];
	return bar;
}