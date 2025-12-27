#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <cstddef>
#include "../math/Vector2.hpp"
#include <numbers>

using BodyID = std::size_t;

struct RigidBody {
	BodyID id;

	Vector2 position;
	Vector2 velocity;
	
	// @brief Mass of body in 
	double mass;
	double height;
	double width;

	// @brief Angle in radians that the body makes with positive horizontal axis
	double angle = (std::numbers::pi / 2);

	// @brief Value between 0 and 1
	double throttle;
};

#endif