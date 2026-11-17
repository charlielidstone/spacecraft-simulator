#ifndef BODY_HPP
#define BODY_HPP

#include "../math/Vector2.hpp"
#include <cstddef>
#include <string>
#include <numbers>

using ObjectID = std::size_t;

enum Colour {
	White,
	Red
};

struct Body {
	ObjectID id;
	std::string name;

	bool isActive = false;

	double width = 10.0;
	double height = 10.0;

	double mass = 1.0;
	Vector2 centreOfMass = { 0.0, 0.0 };
	Vector2 velocity = { 0.0, 0.0 };
	Vector2 position = { 0.0, 0.0 };

	// @brief Angle in radians that the body makes with positive horizontal axis
	//double angle = 0;
	double angle = (std::numbers::pi / 2);

	Colour colour = White;

	virtual ~Body() = default;
};

#endif