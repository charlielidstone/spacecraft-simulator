#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <cstddef>
#include "../math/Vector2.hpp"
#include <numbers>
#include <string>
#include <cmath>
#include "Body.hpp"

struct RigidBody : Body {

	Vector2 centreOfMass = { width / 2, height / 2 }; // pretty sure this doesn't work so I'll have to see how to do this properly

	// @brief Moment of inertia around center of mass, L = Amr²
	const double momOfInertia = (1/12.0)*mass*(std::pow(width,2)+std::pow(height, 2));
	double angularFrequency = 0.0;

	// @brief Value between 0 and 1
	double throttle = 0.0;
};

#endif