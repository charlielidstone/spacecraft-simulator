#ifndef FORCE_HPP
#define FORCE_HPP

#include "../math/Vector2.hpp"
#include "../state/Body.hpp"
#include "../state/RigidBody.hpp"
#include "../state/LargeBody.hpp"
#include <cmath>
#include <iostream>

struct Force {
	virtual ~Force() = default;

	virtual Vector2 computeForce(const Body& body) const = 0;
	virtual double computeTorque(const Body& body) const = 0;
};

class GravityForce : public Force {
public:
	explicit GravityForce(const Vector2& gravityAcceleration) : g(gravityAcceleration) {}
	explicit GravityForce(const Body& body1, const Body& body2) {
		Vector2 distance = body2.position - body1.position;
		double distanceMagnitude = sqrt(distance.x * distance.x + distance.y * distance.y);
		Vector2 unitVector = distance * (1.0 / distanceMagnitude);
		double accelerationMagnitude = G * body2.mass / (distanceMagnitude * distanceMagnitude);
		g = unitVector * accelerationMagnitude;
	};

		Vector2 computeForce(const Body& body) const override {
			// F = mg
			return g * body.mass;
		}

		double computeTorque(const Body& body) const override {
			return 0.0;
		}

	private:
		// @brief Gravitational acceleration. On earth: -9.81
		Vector2 g;
		const double G = 0.0000000000066743;
};

class ThrustForce : public Force {
	public:
		explicit ThrustForce(double maxThrust, ObjectID targetID) : maxThrust(maxThrust), targetID(targetID) {}

		Vector2 computeForce(const Body& body) const override {
			// Only apply thrust to RigidBody objects
			const RigidBody* rigidBody = dynamic_cast<const RigidBody*>(&body);
			if (!rigidBody || targetID != body.id) {
				return { 0.0, 0.0 };
			}

			double thrust = maxThrust * rigidBody->throttle;
			Vector2 forceUnitVector({ std::cos(body.angle), std::sin(body.angle)});
			return forceUnitVector * thrust;
		}

		double computeTorque(const Body& body) const override {
			return 0.0;
		}

	private:
		ObjectID targetID;
		// @brief Max thrust measured in Newtons
		double maxThrust = 0.0;
};

#endif
