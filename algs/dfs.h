#ifndef DFS_H
#define DFS_H

#include <stack>
#include <iostream>
#include <unistd.h>

#include "../game_defns.h"
#include "../game_state.h"

namespace dfs {
	State* solve(State* startState) {
		std::stack<State*> states;
		states.push(startState);

		while(!states.empty()) {
			State* foo = states.top();
			states.pop();

			std::cout << /*"\033[2J" << */"Checking:\n";
			foo->print();
			if(foo->isSolution()) {
				while(!states.empty()) {
					State* top = states.top();
					states.pop();
					delete top;
				}
				return foo;
			}
			else {
				std::vector<State*> bar = foo->next();
				usleep(1000*500);
				for(size_t i=0; i<bar.size(); ++i) {
					states.push(bar[i]);
				}
				delete foo;
			}
		}

		std::cout << "No solution found!" << std::endl;
		return nullptr;
	}
};

#endif