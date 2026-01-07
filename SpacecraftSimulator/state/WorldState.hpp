#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "../state/RigidBody.hpp"
#include "../state/ReferenceMark.hpp"
#include <unordered_map>

struct WorldState {
	double time;
	std::unordered_map<ObjectID, RigidBody*> bodies;
	std::unordered_map<ObjectID, ReferenceMark> referenceMarks;
};

#endif