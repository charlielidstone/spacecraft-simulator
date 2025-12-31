#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <cstddef>
#include "../math/Vector2.hpp"
#include <numbers>
#include <string>

using ObjectID = std::size_t;

struct RigidBody {
	ObjectID id;
	std::string name;	

	// @brief Mass of body in 
	double mass;
	double width;
	double height;

	Vector2 position;
	Vector2 velocity;

	// @brief Angle in radians that the body makes with positive horizontal axis
	//double angle = 0;
	double angle = (std::numbers::pi / 2);

	// @brief Value between 0 and 1
	double throttle;
};

#endif