#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include "game_defns.h"

class State {
private:
	size_t rows;
	size_t cols;
	Colors::ColorsEnum** board;
	
	void makeEmptyBoard(size_t, size_t);
	void deleteBoard();
	short numNeighbors(size_t, size_t) const;
	bool isEndpoint(size_t, size_t) const;
	void getEndpoints(std::vector<std::array<size_t, 2>> &) const;

	static std::unordered_set<Colors::ColorsEnum> boardColors;
	static std::unordered_map<Colors::ColorsEnum, std::array<size_t, 2>> colorStarts;
	static std::unordered_map<Colors::ColorsEnum, std::array<size_t, 2>> colorEnds;

public:
	State(size_t, size_t, std::vector<std::string>);
	State(const std::string &);

	~State();
	State(const State &);
	State & operator=(const State &);

	void initializeColorStarts();

	size_t getRows() const;
	size_t getCols() const;
	size_t numEmpty() const;
	std::vector<Colors::ColorsEnum> getColors() const;

	void print() const;
	void writeToFile(const std::string &) const;
	void printColorStarts() const;

	Colors::ColorsEnum & at(size_t, size_t);
	const Colors::ColorsEnum & at(size_t, size_t) const;
	Colors::ColorsEnum & at(const std::array<size_t, 2> &);
	const Colors::ColorsEnum & at(const std::array<size_t, 2> &) const;

	Colors::ColorsEnum* & operator[](const size_t);
	Colors::ColorsEnum* const & operator[](const size_t) const;

	std::vector<State*> next() const;
	bool isSolution() const;
};

#endif