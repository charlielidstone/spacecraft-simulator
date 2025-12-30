#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "../state/RigidBody.hpp"
#include "../state/ReferenceMark.hpp"
#include <vector>

struct WorldState {
	double time;
	std::vector<RigidBody> bodies;
	std::vector<ReferenceMark> referenceMarks;
};

#endif