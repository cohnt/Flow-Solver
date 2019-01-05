#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "game_defns.h"

class State {
private:
	size_t rows;
	size_t cols;
	Colors::ColorsEnum** board;
	void makeEmptyBoard(size_t, size_t);
	void deleteBoard();

public:
	State(size_t, size_t);
	State(size_t, size_t, std::vector<std::string>);
	State(const std::string &);

	~State();
	State(const State &);
	State & operator=(const State &);

	size_t getRows() const;
	size_t getCols() const;

	void print() const;
	void writeToFile(const std::string &) const;

	Colors::ColorsEnum & at(size_t, size_t);
	const Colors::ColorsEnum & at(size_t, size_t) const;

	Colors::ColorsEnum* operator[](const size_t);
	Colors::ColorsEnum* const operator[](const size_t) const;
};

#endif