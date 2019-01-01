#include <iostream>
#include <fstream>

#include "../game_state.h"

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cout << "Usage: ./print_state_file [filename]" << std::endl;
		exit(1);
	}

	std::ifstream in(argv[1]);
	int rows, cols;

	in >> rows;
	in >> cols;

	std::vector<std::string> lines;
	std::string line;
	while(std::getline(in >> std::ws, line)) {
		lines.push_back(line);
	}

	State state(rows, cols, lines);

	state.print();

	in.close();

	return 0;
}