#ifndef BFS_H
#define BFS_H

#include <queue>
#include <iostream>
#include <unistd.h>

#include "../game_defns.h"
#include "../game_state.h"

namespace bfs {
	State* solve(State* startState) {
		std::queue<State*> states;
		states.push(startState);

		while(!states.empty()) {
			State* foo = states.front();
			states.pop();

			// std::cout << "\033[2J" << "Checking:\n\n";
			// foo->print();
			// usleep(1000*100);
			if(foo->isSolution()) {
				while(!states.empty()) {
					State* front = states.front();
					states.pop();
					delete front;
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
		return nullptr;
	}
};

#endif