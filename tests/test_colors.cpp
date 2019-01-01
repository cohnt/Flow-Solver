#include <iostream>
#include <string>

#include "../game_defns.h"

int main() {
	std::cout << Colors::colorToTermCode.at(Colors::red) << "red" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::blue) << "blue" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::yellow) << "yellow" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::green) << "green" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::orange) << "orange" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::cyan) << "cyan" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::magenta) << "magenta" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::maroon) << "maroon" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::purple) << "purple" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::gray) << "gray" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::white) << "white" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::bright_green) << "bright_green" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::tan) << "tan" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::dark_blue) << "dark_blue" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::dark_cyan) << "dark_cyan" << std::endl;
	std::cout << Colors::colorToTermCode.at(Colors::pink) << "pink" << std::endl;

	std::cout << Colors::reset;

	return 0;
}