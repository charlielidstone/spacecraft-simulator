#ifndef FORCE_HPP
#define FORCE_HPP

#include "../math/Vector2.hpp"
#include "RigidBody.hpp"

struct Force {
	virtual ~Force() = default;

	virtual Vector2 computeForce(const RigidBody& Body) const = 0;
	virtual double computeTorque(const RigidBody& Body) const = 0;
};

class GravityForce : public Force {
	public:
		explicit GravityForce(const Vector2& gravityAcceleration) : g(gravityAcceleration) {}

		Vector2 computeForce(const RigidBody& body) const override {
			return g * body.mass;
		}

		double computeTorque(const RigidBody& body) const override {
			return 0.0;
		}

	private:
		// @brief Gravitational acceleration. On earth: -9.81
		Vector2 g;
};

#endif
