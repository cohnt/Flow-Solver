#ifndef GAME_DEFNS_H
#define GAME_DEFNS_H

#include <unordered_map>
#include <string>

namespace Colors {
	enum ColorsEnum : int {
		red
		blue
		yellow
		green
		orange
		cyan
		magenta
		maroon
		purple
		gray
		white
		bright_green
		tan
		dark_blue
		dark_cyan
		pink
	};

	const std::unordered_map<char, int> charToColor({
		{R, red},
		{B, blue},
		{Y, yellow},
		{G, green},
		{O, orange},
		{C, cyan},
		{M, magenta},
		{m, maroon},
		{P, purple},
		{A, gray},
		{W, white},
		{g, bright_green},
		{T, tan},
		{b, dark_blue},
		{c, dark_cyan},
		{p, pink}
	});
	const std::unordered_map<int, char> colorToChar({
		{red, R},
		{blue, B},
		{yellow, Y},
		{green, G},
		{orange, O},
		{cyan, C},
		{magenta, M},
		{maroon, m},
		{purple, P},
		{gray, A},
		{white, W},
		{bright_green, g},
		{tan, T},
		{dark_blue, b},
		{dark_cyan, c},
		{pink, p}
	});
	const std::unordered_map<int, std::string> colorToTermCode({
		{red, "\033[31m"},
		{blue, "\033[34m"},
		{yellow, "\033[33m"},
		{green, "\033[32m"},
		{orange, "\033[1m\033[33m"},
		{cyan, "\033[36m"},
		{magenta, "\033[35m"},
		{maroon, "\033[1m\033[31m"},
		{purple, "\033[1m\033[35m"},
		{gray, "\033[1m\033[37m"},
		{white, "\033[37m"},
		{bright_green, "\033[1m\033[32m"},
		{tan, "\033[1m\033[33m"},
		{dark_blue, "\033[1m\033[34m"},
		{dark_cyan, "\033[1m\033[36m"},
		{pink, "\033[1m\033[31m"}
	});

	const std::string reset = "\003[0m";
};

#endif