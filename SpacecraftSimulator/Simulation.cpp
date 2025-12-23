#include "simulation/Simulation.hpp"
#include <iostream>

Simulation::Simulation(double timestep) : dt(timestep) {
	state.body.mass = 1.0;
	state.body.position = { 0.0, 10.0 };
	state.body.velocity = { 0.0, 0.0 };
}

void Simulation::step() {
	Vector2 gravityForce(0.0, -9.80 * state.body.mass);

	Vector2 acceleration = gravityForce * (1.0 / state.body.mass);

	state.body.velocity += acceleration * dt;
	state.body.position += state.body.velocity * dt;

	state.time += dt;
}

const WorldState& Simulation::getState() const {
	return state;
}