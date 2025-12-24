#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include "../math/Vector2.hpp"

struct RigidBody {
	Vector2 position;
	Vector2 velocity;
	double mass;
};

#endif