#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <queue>

#include "game_defns.h"
#include "game_state.h"
#include "tree/tree.h"
#include "algs/dfs.h"

struct ConfigStruct {
	Algorithms::AlgorithmsEnum alg;
};

bool checkFormat(const State &);
void loadConfigFile(ConfigStruct &, const std::string &);

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cout << "Usage: ./solve [puzzle file] [config file]" << std::endl;
		exit(1);
	}

	State* startState = new State(argv[1]);
	std::cout << "Successfully opened puzzle " << argv[1] << std::endl;

	startState->initializeColorStarts();

	// size_t rows = startState.rows();
	// size_t cols = startState.cols();

	if(!checkFormat(*startState)) {
		exit(1);
	}

	ConfigStruct config;
	loadConfigFile(config, argv[2]);
	std::cout << "Using algorithm " << Algorithms::algorithmNamesToString.at(config.alg) << std::endl;

	startState->print();

	// auto colors = startState->getColors();
	// for(auto iter = colors.begin(); iter != colors.end(); ++iter) {
	// 	std::cout << Colors::colorToChar.at(*iter) << std::endl;
	// }

	State* endState;

	switch(config.alg) {
		case Algorithms::dfs:
			endState = dfs::solve(startState);
			break;
		default:
			exit(1); //TODO
			break;
	};

	if(endState == nullptr) {
		return 0;
	}

	std::cout << std::endl << "Solution:" << std::endl;
	endState->print();

	delete endState;

	return 0;
}

//Check that a state object is valid for starting out.
bool checkFormat(const State & state) {
	//The number of squares of a given color
	std::unordered_map<Colors::ColorsEnum, int> counts;

	//Zero-initialize every color
	for(auto iter = Colors::charToColor.begin(); iter != Colors::charToColor.end(); ++iter) {
		counts[static_cast<Colors::ColorsEnum>(iter->second)] = 0;
	}

	size_t rows = state.getRows();
	size_t cols = state.getCols();

	//Count up how many there are of each colored square (except empty squares, of course)
	for(size_t i=0; i<rows; ++i) {
		for(size_t j=0; j<cols; ++j) {
			Colors::ColorsEnum color = state[i][j];
			if(color != Colors::empty) {
				++counts[color];
			}
		}
	}

	//Check that a color is either not present, or has exactly 2 squares.
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

//Read in a config file
void loadConfigFile(ConfigStruct & config, const std::string & fname) {
	std::ifstream in(fname.c_str());

	std::string algName;
	in >> algName;

	config.alg = Algorithms::stringToAlgorithmNames.at(algName);
}