#include <iostream>
#include <fstream>

#include "../game_state.h"

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cout << "Usage: ./print_state_file [filename]" << std::endl;
		exit(1);
	}

	State state(argv[1]);
	state.print();

	return 0;
}