#ifndef SIMPLE_ASTAR_H
#define SIMPLE_ASTAR_H

#include <queue>
#include <iostream>
#include <unistd.h>

#include "flow_alg.h"
#include "../game_defns.h"
#include "../game_state.h"

class SimpleAstar : public FlowAlg {
public:
	class Compare {
	public:
		bool operator() (State* l, State* r) {
			int lScore = l->numEmpty();
			int rScore = r->numEmpty();
			return lScore > rScore;
		}
	};
	virtual State* solve(State* startState) const {
		std::priority_queue<State*, std::vector<State*>, Compare> states;
		states.push(startState);

		while(!states.empty()) {
			State* foo = states.top();
			states.pop();

			// std::cout << "\033[2J" << "Checking:\n\n";
			// foo->print();
			// usleep(1000*100);
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
		return nullptr;
	}
};

#endif