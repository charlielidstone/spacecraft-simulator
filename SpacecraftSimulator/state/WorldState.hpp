#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include "../state/Body.hpp"
#include "../state/ReferenceMark.hpp"
#include <unordered_map>

struct WorldState {
	double time;
	std::unordered_map<ObjectID, Body*> bodies;
	Body* activeBody = nullptr;
	std::unordered_map<ObjectID, ReferenceMark> referenceMarks;
};

#endif