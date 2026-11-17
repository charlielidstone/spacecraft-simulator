#ifndef LARGEBODY_HPP
#define LARGEBODY_HPP

#include <cstddef>
#include "../math/Vector2.hpp"
#include <numbers>
#include <string>
#include <cmath>
#include "Body.hpp"

struct LargeBody : Body {
	double radius = 0.0;

	LargeBody() = default;

	LargeBody(double r) 
    : radius(r) {
        width = r * 2;
        height = r * 2;
        centreOfMass = {r, r};
	}
};

#endif