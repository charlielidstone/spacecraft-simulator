#include "simulation/Simulation.hpp"
#include "math/Vector2.hpp"
#include <iostream>
#include <cmath>

Simulation::Simulation(double timestep) : dt(timestep) {
	ObjectID nextID = 0;

	state.time = 0.0;

	RigidBody rocket = {
		.id = nextID++,
		.name = "rocket",
		.mass = 100.0,
		.width = 10.0,
		.height = 30.0,
		.position = { 10.0, 50.0 },
		.velocity = { 0.0, -40.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(rocket.id, rocket);

	RigidBody otherRocket = {
		.id = nextID++,
		.name = "otherRocket",
		.mass = 100.0,
		.width = 30.0,
		.height = 90.0,
		.position = { -10.0, -30.0 },
		.velocity = { 0.0, 70.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(otherRocket.id, otherRocket);

	RigidBody rocket3 = {
		.id = nextID++,
		.name = "rocket3",
		.mass = 100.0,
		.width = 40.0,
		.height = 20.0,
		.position = { -40.0, 30.0 },
		.velocity = { 10.0, 0.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(rocket3.id, rocket3);

	//forces.push_back(std::make_unique<GravityForce>(Vector2{ 0.0, -9.81 }));
	forces.push_back(std::make_unique<ThrustForce>(10000, 0));
}

void Simulation::simulateGpuDelay() {
	const int iterations = 400000;
	volatile double result = 0.0;
	
	for (int i = 0; i < iterations; i++) {
		result += std::sin(i * 0.001) * std::cos(i * 0.001);
	}
}

void Simulation::step(InputState& input) {
	std::cout << "Frame count: " << count++ << "\n";
	std::cout << "-------------------\n";
	for (auto& [id, body] : state.bodies) {
		Vector2 netForce{ 0.0, 0.0 };
		double netTorque = 0.0;

		for (const auto& force : forces) {
			netForce += force->computeForce(body);
			netTorque += force->computeTorque(body);
		}

		Vector2 acceleration = netForce / body.mass;
		body.velocity += acceleration * dt;
		body.position += body.velocity * dt;

		/*netTorque = dL / dt
		dL */

		std::cout << "Object: " << body.name << "\n";
		std::cout << "Net Force: (" << netForce.x << ", " << netForce.y << ")\n";
		std::cout << "Mass: " << body.mass << "\n";
		std::cout << "Position: (" << body.position.x << ", " << body.position.y << ")\n";
		std::cout << "Velocity: (" << body.velocity.x << ", " << body.velocity.y << ")\n";
		std::cout << "Acceleration: (" << acceleration.x << ", " << acceleration.y << ")\n";
		std::cout << "Rotation: " << (body.angle * 180 / 3.1415926535) << "\n";
		std::cout << "dt: " << dt << "\n";

		state.time += dt;

		std::cout << "-------------------\n";
	}


	//simulateGpuDelay();
}

const WorldState& Simulation::getState() const {
	return state;
}