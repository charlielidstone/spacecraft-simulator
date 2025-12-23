#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "BodyState.hpp"

struct WorldState {
	double time;
	BodyState body;
};

#endif