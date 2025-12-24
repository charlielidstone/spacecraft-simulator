#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "../physics/RigidBody.hpp"

struct WorldState {
	double time;
	RigidBody body;
};

#endif