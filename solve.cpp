#include <iostream>
#include <unordered_map>
#include <string>

#include "game_defns.h"
#include "game_state.h"
#include "tree/tree.h"

bool checkFormat(const State &);

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cout << "Usage: ./solve [puzzle file] [config file]" << std::endl;
		exit(1);
	}

	State startState(argv[1]);
	std::cout << "Successfully opened puzzle " << argv[1] << std::endl;

	// size_t rows = startState.rows();
	// size_t cols = startState.cols();

	if(!checkFormat(startState)) {
		exit(1);
	}

	

	startState.print();

	return 0;
}

//Check that a state object is valid for starting out.
bool checkFormat(const State & state) {
	std::unordered_map<Colors::ColorsEnum, int> counts;

	for(auto iter = Colors::charToColor.begin(); iter != Colors::charToColor.end(); ++iter) {
		counts[static_cast<Colors::ColorsEnum>(iter->second)] = 0;
	}

	size_t rows = state.rows();
	size_t cols = state.cols();

	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			Colors::ColorsEnum color = state[i][j];
			if(color != Colors::empty) {
				++counts[color];
			}
		}
	}

	for(auto iter = counts.begin(); iter != counts.end(); ++iter) {
		if(iter->second != 0 && iter->second != 2) {
			std::cout << "Error: found " << (iter->second) << " squares with color "
			          << Colors::colorToTermCode.at(iter->first) << Colors::colorToChar.at(iter->first)
			          << Colors::reset << std::endl;
			return false;
		}
	}

	return true;
}