#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <cstddef>
#include "../math/Vector2.hpp"
#include <numbers>
#include <string>
#include <cmath>

using ObjectID = std::size_t;

enum Colour {
	White,
	Red
};

struct RigidBody {
	ObjectID id;
	std::string name;	

	bool isActive = false;

	// @brief Mass of body in 
	double width = 0.0;
	double height = 0.0;

	double mass = 1.0;
	Vector2 velocity = { 0.0, 0.0 };
	Vector2 position = { 0.0, 0.0 };

	// @brief Moment of inertia around center of mass, L = Amr²
	const double momOfInertia = (1/12.0)*mass*(std::pow(width,2)+std::pow(height, 2));
	double angularFrequency = 0.0;

	// @brief Angle in radians that the body makes with positive horizontal axis
	//double angle = 0;
	double angle = (std::numbers::pi / 2);

	// @brief Value between 0 and 1
	double throttle = 0.0;

	Colour colour = White;
};

#endif