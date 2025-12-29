#include "simulation/Simulation.hpp"
#include "math/Vector2.hpp"
#include <iostream>
#include <cmath>

Simulation::Simulation(double timestep) : dt(timestep) {
	state.time = 0.0;
	
	state.body.mass = 100.0;
	state.body.width = 10.0;
	state.body.height = 30.0;
	state.body.position = { 0.0, 0.0 };
	state.body.velocity = { 0.0, -10.0 };
	state.body.id = 0;
	state.body.throttle = 0.0;

	//forces.push_back(std::make_unique<GravityForce>(Vector2{ 0.0, -9.81 }));
	forces.push_back(std::make_unique<ThrustForce>(10000, 0));
}

void Simulation::simulateGpuDelay() {
	const int iterations = 400000;
	volatile double result = 0.0;
	
	for (int i = 0; i < iterations; ++i) {
		result += std::sin(i * 0.001) * std::cos(i * 0.001);
	}
}

void Simulation::step(InputState& input) {
	Vector2 netForce{ 0.0, 0.0 };
	double netTorque = 0.0;

	if (input.shiftPressed || input.WPressed) {
		state.body.throttle = 1.0;
	} else if (input.SPressed) {
		state.body.throttle = -1.0;
	} else {
		state.body.throttle = 0.0;
	}

	for (const auto& force : forces) {
		netForce += force->computeForce(state.body);
		netTorque += force->computeTorque(state.body);
	}

	Vector2 acceleration = netForce / state.body.mass;
	state.body.velocity += acceleration * dt;
	state.body.position += state.body.velocity * dt;
	
	std::cout << "Net Force: (" << netForce.x << ", " << netForce.y << ")\n";
	std::cout << "Mass: " << state.body.mass << "\n";
	std::cout << "Position: (" << state.body.position.x << ", " << state.body.position.y << ")\n";
	std::cout << "Velocity: (" << state.body.velocity.x << ", " << state.body.velocity.y << ")\n";
	std::cout << "Acceleration: (" << acceleration.x << ", " << acceleration.y << ")\n";
	std::cout << "dt: " << dt << "\n";

	state.time += dt;

	std::cout << "Frame count: " << count++ << "\n";
	std::cout << "-------------------\n";

	//simulateGpuDelay();
}

const WorldState& Simulation::getState() const {
	return state;
}