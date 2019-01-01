#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cout << "Usage: ./print_state_file [filename]" << std::endl;
	}

	std::ifstream in(argv[1]);

	in.close();

	return 0;
}