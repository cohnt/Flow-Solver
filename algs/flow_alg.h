#ifndef FLOW_ALG_H
#define FLOW_ALG_H

#include "../game_state.h"

class FlowAlg {
public:
	virtual ~FlowAlg() {}
	virtual State* solve(State* startState) const = 0;
};

#endif