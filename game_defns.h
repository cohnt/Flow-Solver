#ifndef GAME_DEFNS_H
#define GAME_DEFNS_H

#include <unordered_map>
#include <string>

namespace Colors {
	enum ColorsEnum : int {
		empty,
		red,
		blue,
		yellow,
		green,
		orange,
		cyan,
		magenta,
		maroon,
		purple,
		gray,
		white,
		bright_green,
		tan,
		dark_blue,
		dark_cyan,
		pink
	};

	const std::unordered_map<char, int> charToColor({
		{'.', Colors::empty},
		{'R', Colors::red},
		{'B', Colors::blue},
		{'Y', Colors::yellow},
		{'G', Colors::green},
		{'O', Colors::orange},
		{'C', Colors::cyan},
		{'M', Colors::magenta},
		{'m', Colors::maroon},
		{'P', Colors::purple},
		{'A', Colors::gray},
		{'W', Colors::white},
		{'g', Colors::bright_green},
		{'T', Colors::tan},
		{'b', Colors::dark_blue},
		{'c', Colors::dark_cyan},
		{'p', Colors::pink}
	});
	const std::unordered_map<int, char> colorToChar({
		{Colors::empty, '.'},
		{Colors::red, 'R'},
		{Colors::blue, 'B'},
		{Colors::yellow, 'Y'},
		{Colors::green, 'G'},
		{Colors::orange, 'O'},
		{Colors::cyan, 'C'},
		{Colors::magenta, 'M'},
		{Colors::maroon, 'm'},
		{Colors::purple, 'P'},
		{Colors::gray, 'A'},
		{Colors::white, 'W'},
		{Colors::bright_green, 'g'},
		{Colors::tan, 'T'},
		{Colors::dark_blue, 'b'},
		{Colors::dark_cyan, 'c'},
		{Colors::pink, 'p'}
	});
	const std::unordered_map<int, std::string> colorToTermCode({
		{Colors::empty, "\033[0m"},
		{Colors::red, "\033[91m"},
		{Colors::blue, "\033[94m"},
		{Colors::yellow, "\033[93m"},
		{Colors::green, "\033[32m"},
		{Colors::orange, "\033[33m"},
		{Colors::cyan, "\033[96m"},
		{Colors::magenta, "\033[95m"},
		{Colors::maroon, "\033[31m"},
		{Colors::purple, "\033[35m"},
		{Colors::gray, "\033[90m"},
		{Colors::white, "\033[37m"},
		{Colors::bright_green, "\033[92m"},
		{Colors::tan, "\033[33m"},
		{Colors::dark_blue, "\033[34m"},
		{Colors::dark_cyan, "\033[36m"},
		{Colors::pink, "\033[95m"}
	});

	const std::string reset = "\033[0m";
};

namespace Algorithms {
	enum AlgorithmsEnum : int {
		bfs,
		dfs
	};

	const std::unordered_map<Algorithms::AlgorithmsEnum, std::string> algorithmNamesToString({
		{Algorithms::bfs, "bfs"},
		{Algorithms::dfs, "dfs"}
	});
	const std::unordered_map<std::string, Algorithms::AlgorithmsEnum> stringToAlgorithmNames({
		{"bfs", Algorithms::bfs},
		{"dfs", Algorithms::dfs}
	});
};


#endif