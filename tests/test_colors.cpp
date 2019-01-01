#include <iostream>
#include <string>

#include "../game_defns.h"

int main() {
	std::cout << Colors::colorToTermCode.at(Colors::red) << "red" << std::endl;

	return 0;
}