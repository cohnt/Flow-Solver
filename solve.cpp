#include <iostream>
#include <unordered_map>
#include <string>

#include "game_defns.h"
#include "game_state.h"
#include "tree/tree.h"

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cout << "Usage: ./solve [puzzle file] [algorithm]" << std::endl;
		std::cout << "Available algorithms:" << std::endl;
		for(auto iter = AlgorithmNames::algorithmNamesToString.begin(); iter != AlgorithmNames::algorithmNamesToString.end(); ++iter) {
			std::cout << '\t' << iter->second << std::endl;
		}
		exit(1);
	}

	return 0;
}