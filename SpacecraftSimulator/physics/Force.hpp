#ifndef FORCE_HPP
#define FORCE_HPP

#include "../math/Vector2.hpp"
#include "../state/RigidBody.hpp"
#include <cmath>
#include <iostream>

struct Force {
	virtual ~Force() = default;

	virtual Vector2 computeForce(const RigidBody& body) const = 0;
	virtual double computeTorque(const RigidBody& body) const = 0;
};

class GravityForce : public Force {
	public:
		explicit GravityForce(const Vector2& gravityAcceleration) : g(gravityAcceleration) {}

		Vector2 computeForce(const RigidBody& body) const override {
			// F = mg
			return g * body.mass;
		}

		double computeTorque(const RigidBody& body) const override {
			return 0.0;
		}

	private:
		// @brief Gravitational acceleration. On earth: -9.81
		Vector2 g;
};

class ThrustForce : public Force {
	public:
		explicit ThrustForce(double maxThrust, ObjectID targetID) : maxThrust(maxThrust), targetID(targetID) {}

		Vector2 computeForce(const RigidBody& body) const override {
			if (targetID != body.id) {
				return { 0.0, 0.0 };
			}

			double thrust = maxThrust * body.throttle;
			Vector2 forceUnitVector({ std::cos(body.angle), std::sin(body.angle)});
			return forceUnitVector * thrust;
		}

		double computeTorque(const RigidBody& body) const override {
			return 0.0;
		}

	private:
		ObjectID targetID;
		// @brief Max thrust measured in Newtons
		double maxThrust = 0.0;
};

#endif
