#include "simulation/Simulation.hpp"
#include "math/Vector2.hpp"
#include <iostream>

Simulation::Simulation(double timestep) : dt(timestep) {
	state.time = 0.0;
	
	state.body.mass = 10.0;
	state.body.position = { 0.0, 0.0 };
	state.body.velocity = { 0.0, 0.0 };
	state.body.id = 0;
	state.body.throttle = 1.0;

	//forces.push_back(std::make_unique<GravityForce>(Vector2{ 0.0, -9.81 }));
	//forces.push_back(std::make_unique<ThrustForce>(98.2, 0));
}

void Simulation::step() {
	Vector2 netForce{ 0.0, 0.0 };
	double netTorque = 0.0;

	for (const auto& force : forces) {
		netForce += force->computeForce(state.body);
		netTorque += force->computeTorque(state.body);
	}

	std::cout << "Net Force: (" << netForce.x << ", " << netForce.y << ")\n";

	Vector2 acceleration = netForce / state.body.mass;

	state.body.velocity += acceleration * dt;
	state.body.position += state.body.velocity * dt;

	state.time += dt;
}

const WorldState& Simulation::getState() const {
	return state;
}