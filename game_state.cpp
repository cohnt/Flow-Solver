#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <algorithm>

#include "game_state.h"

std::unordered_set<Colors::ColorsEnum> State::boardColors;
std::unordered_map<Colors::ColorsEnum, std::array<size_t, 2>> State::colorStarts;
std::unordered_map<Colors::ColorsEnum, std::array<size_t, 2>> State::colorEnds;

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
short State::numNeighbors(size_t row, size_t col) const {
	short num = 0;

	// std::cout << "Checking if " << row << "," << col << " is an endpoint." << std::endl;

	if(row > 0) {
		num += (board[row][col] == board[row-1][col]);
	}
	if(row+1 < rows) {
		num += (board[row][col] == board[row+1][col]);
	}
	if(col > 0) {
		num += (board[row][col] == board[row][col-1]);
	}
	if(col+1 < cols) {
		num += (board[row][col] == board[row][col+1]);
	}

	return num;
}
bool State::isEndpoint(size_t row, size_t col) const {
	short num = numNeighbors(row, col);
	return num == 0 || num == 1;
}
void State::getEndpoints(std::vector<std::array<size_t, 2>> & endpoints) const {
	std::unordered_map<Colors::ColorsEnum, bool> foundEndpoint;
	auto colors = getColors();
	for(auto iter = colors.begin(); iter != colors.end(); ++iter) {
		auto color = *iter;
		foundEndpoint[color] = false;
	}

	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			if(board[i][j] != Colors::empty && isEndpoint(i, j)) {
				std::array<size_t, 2> start = colorStarts[board[i][j]];
				std::array<size_t, 2> end = colorEnds[board[i][j]];
				std::array<size_t, 2> point;
				point[0] = i;
				point[1] = j;
				if(point != start && point != end) {
					foundEndpoint[board[i][j]] = true;
					endpoints.push_back(std::array<size_t, 2>{i, j});
				}
			}
		}
	}

	// std::cout << "Raw endpoints list: ";
	// for(size_t i=0; i<endpoints.size(); ++i) {
	// 	std::cout << '(' << endpoints[i][0] << ',' << endpoints[i][1] << ") ";
	// }
	// std::cout << std::endl;

	for(auto iter = colors.begin(); iter != colors.end(); ++iter) {
		auto color = *iter;
		if(!foundEndpoint[color]) {
			std::array<size_t, 2> end = colorEnds[color];
			if(numNeighbors(end[0], end[1]) == 0) {
				endpoints.push_back(colorStarts[color]);
			}
		}
	}
	// std::cout << "Final endpoints list: ";
	// for(size_t i=0; i<endpoints.size(); ++i) {
	// 	std::cout << '(' << endpoints[i][0] << ',' << endpoints[i][1] << ") ";
	// }
	// std::cout << std::endl;
	// std::cout << "\n\n\n";
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

			if(board[i][j] != Colors::empty) {
				boardColors.insert(board[i][j]);
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
			//No need to adjust boardColors, because boardColors is static
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
				//No need to adjust boardColors, because boardColors is static
			}
		}
	}
	return *this;
}

void State::initializeColorStarts() {
	if(colorStarts.size() != 0) {
		assert(false && "You already initialized colorStarts!");
	}
	else if(colorEnds.size() != 0) {
		assert(false && "You already initialized colorEnds!");
	}
	else if(boardColors.size() == 0) {
		assert(false && "You haven't initialized boardColors yet!");
	}

	Colors::ColorsEnum color;
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			color = board[i][j];
			if(color != Colors::empty) {
				if(colorStarts.find(color) == colorStarts.end()) {
					colorStarts[color] = std::array<size_t, 2>{i, j};
					// std::cout << Colors::colorToChar.at(color) << " starts at " << i << "," << j << std::endl;
				}
				else {
					colorEnds[color] = std::array<size_t, 2>{i, j};
					// std::cout << Colors::colorToChar.at(color) << " ends at " << i << "," << j << std::endl;
				}
			}
		}
	}
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
std::vector<Colors::ColorsEnum> State::getColors() const {
	//
	return std::vector<Colors::ColorsEnum>(boardColors.begin(), boardColors.end());
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
void State::printColorStarts() const {
	for(auto iter = colorStarts.begin(); iter != colorStarts.end(); ++iter) {
		std::cout << iter->first << "/" << Colors::colorToChar.at(iter->first) << ": " << (iter->second)[0] << "," << (iter->second)[1] << "\n";
	}
}

Colors::ColorsEnum & State::at(size_t row, size_t col) {
	Colors::ColorsEnum & foo = board[row][col];
	return foo;
}
const Colors::ColorsEnum & State::at(size_t row, size_t col) const {
	const Colors::ColorsEnum & foo = board[row][col];
	return foo;
}
Colors::ColorsEnum & State::at(const std::array<size_t, 2> & point) {
	Colors::ColorsEnum & foo = board[point[0]][point[1]];
	return foo;
}
const Colors::ColorsEnum & State::at(const std::array<size_t, 2> & point) const {
	const Colors::ColorsEnum & foo = board[point[0]][point[1]];
	return foo;
}

Colors::ColorsEnum* & State::operator[](const size_t row) {
	Colors::ColorsEnum* & bar = board[row];
	return bar;
}
Colors::ColorsEnum* const & State::operator[](const size_t row) const {
	Colors::ColorsEnum* const & bar = board[row];
	return bar;
}

std::vector<State*> State::next() const {
	std::vector<State*> states;
	std::vector<std::array<size_t, 2>> endpoints;
	getEndpoints(endpoints);

	for(auto iter = endpoints.begin(); iter != endpoints.end(); ++iter) {
		std::array<size_t, 2> point = *iter;

		//Check neighboring tiles, and add if possible
		if(point[0] > 0) {
			if(board[point[0]-1][point[1]] == Colors::empty) {
				State* state = new State(*this);
				state->at(point[0]-1, point[1]) = this->at(point);
				states.push_back(state);
			}
		}
		if(point[0]+1 < rows) {
			if(board[point[0]+1][point[1]] == Colors::empty) {
				State* state = new State(*this);
				state->at(point[0]+1, point[1]) = this->at(point);
				states.push_back(state);
			}
		}
		if(point[1] > 0) {
			if(board[point[0]][point[1]-1] == Colors::empty) {
				State* state = new State(*this);
				state->at(point[0], point[1]-1) = this->at(point);
				states.push_back(state);
			}
		}
		if(point[1]+1 < cols) {
			if(board[point[0]][point[1]+1] == Colors::empty) {
				State* state = new State(*this);
				state->at(point[0], point[1]+1) = this->at(point);
				states.push_back(state);
			}
		}
	}

	return states;
}

bool State::isSolution() const {
	//The board should be completely filled, and getEndpoints should return an empty list
	if(numEmpty() != 0) {
		return false;
	}
	else {
		std::vector<std::array<size_t, 2>> endpoints;
		getEndpoints(endpoints);
		return endpoints.empty();
	}
}