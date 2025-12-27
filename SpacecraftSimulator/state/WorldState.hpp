#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "../state/RigidBody.hpp"

struct WorldState {
	double time;
	RigidBody body;
};

#endif