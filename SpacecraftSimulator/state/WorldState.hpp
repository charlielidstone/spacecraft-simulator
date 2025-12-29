#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "../state/RigidBody.hpp"
#include <vector>

struct WorldState {
	double time;
	RigidBody body;
	//std::vector<RigidBody> bodies;
};

#endif