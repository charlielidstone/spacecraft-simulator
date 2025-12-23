#ifndef BODYSTATE_HPP
#define BODYSTATE_HPP

#include "../math/Vector2.hpp"

struct BodyState {
	Vector2 position;
	Vector2 velocity;
	double mass;
};

#endif