#ifndef DFS_H
#define DFS_H

#include <stack>
#include <iostream>

#include "../game_defns.h"
#include "../game_state.h"

namespace dfs {
	State* solve(State* startState) {
		std::stack<State*> states;
		states.push(startState);

		while(!states.empty()) {
			State* foo = states.top();
			states.pop();

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
				for(size_t i=0; i<bar.size(); ++i) {
					states.push(bar[i]);
				}
				delete foo;
			}
		}

		std::cout << "No solution found!" << std::endl;
		return startState;
	}
};

#endif