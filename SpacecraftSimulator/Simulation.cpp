#include "simulation/Simulation.hpp"
#include "math/Vector2.hpp"
#include <iostream>
#include <cmath>

Simulation::Simulation(double timestep) : dt(timestep) {
	state.time = 0.0;

	state.bodies.resize(1);
	state.bodies[0].mass = 100.0;
	state.bodies[0].width = 10.0;
	state.bodies[0].height = 30.0;
	state.bodies[0].position = { 0.0, 0.0 };
	state.bodies[0].velocity = { 0.0, -10.0 };
	state.bodies[0].id = 0;
	state.bodies[0].throttle = 0.0;

	forces.push_back(std::make_unique<GravityForce>(Vector2{ 0.0, -9.81 }));
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
	Vector2 netForce{ 0.0, 0.0 };
	double netTorque = 0.0;

	if (input.shiftPressed || input.WPressed) {
		state.bodies[0].throttle = 1.0;
	} else if (input.SPressed) {
		state.bodies[0].throttle = -1.0;
	} else {
		state.bodies[0].throttle = 0.0;
	}

	if (input.APressed) {
		state.bodies[0].angle -= (3.1415926535 / 180);
	} else if (input.DPressed) {
		state.bodies[0].angle += (3.1415926535 / 180);
	}

	for (const auto& force : forces) {
		netForce += force->computeForce(state.bodies[0]);
		netTorque += force->computeTorque(state.bodies[0]);
	}

	Vector2 acceleration = netForce / state.bodies[0].mass;
	state.bodies[0].velocity += acceleration * dt;
	state.bodies[0].position += state.bodies[0].velocity * dt;
	
	std::cout << "Net Force: (" << netForce.x << ", " << netForce.y << ")\n";
	std::cout << "Mass: " << state.bodies[0].mass << "\n";
	std::cout << "Position: (" << state.bodies[0].position.x << ", " << state.bodies[0].position.y << ")\n";
	std::cout << "Velocity: (" << state.bodies[0].velocity.x << ", " << state.bodies[0].velocity.y << ")\n";
	std::cout << "Acceleration: (" << acceleration.x << ", " << acceleration.y << ")\n";
	std::cout << "Rotation: " << (state.bodies[0].angle * 180 / 3.1415926535) << "\n";
	std::cout << "dt: " << dt << "\n";

	state.time += dt;

	std::cout << "Frame count: " << count++ << "\n";
	std::cout << "-------------------\n";

	//simulateGpuDelay();
}

const WorldState& Simulation::getState() const {
	return state;
}