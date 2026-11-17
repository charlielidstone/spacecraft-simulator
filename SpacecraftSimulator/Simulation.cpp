#include "simulation/Simulation.hpp"
#include "math/Vector2.hpp"
#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <string>

Simulation::Simulation(double timestep) : dt(timestep) {
	ObjectID nextID = 0;

	state.time = 0.0;

	RigidBody* rocket = new RigidBody();
	rocket->id = nextID++;
	rocket->name = "rocket";
	rocket->width = 10.0;
	rocket->height = 30.0;
	rocket->mass = 100.0;
	rocket->velocity = { 0.0, -40.0 };
	rocket->position = { 10.0, 50.0 };
	rocket->throttle = 0.0;

	state.bodies.emplace(rocket->id, rocket);

	// Dummy objects with randomised size, mass, position and velocity
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<double> posDist(-500.0, 500.0);
	std::uniform_real_distribution<double> velDist(-50.0, 50.0);
	std::uniform_real_distribution<double> sizeDist(5.0, 40.0);
	std::uniform_real_distribution<double> massDist(10.0, 1000.0);

	const int dummyCount = 1000;
	for (int i = 0; i < dummyCount; i++) {
		RigidBody* dummy = new RigidBody();
		dummy->id = nextID++;
		dummy->name = "dummy_" + std::to_string(i);
		dummy->width = sizeDist(rng);
		dummy->height = sizeDist(rng);
		dummy->mass = massDist(rng);
		dummy->position = { posDist(rng), posDist(rng) };
		dummy->velocity = { velDist(rng), velDist(rng) };
		dummy->throttle = 0.0;

		state.bodies.emplace(dummy->id, dummy);
	}


	LargeBody* Sun = new LargeBody(50.0);
	Sun->id = nextID++;
	Sun->name = "Sun";
	//Sun->radius = 696'340'000.0;
	Sun->mass = 1.989e30;
	Sun->position = { 0.0, 0.0 };

	std::cout << "Sun->width: " << Sun->width << std::endl;

	state.bodies.emplace(Sun->id, Sun);

	std::cout << "Number of objects: " << nextID << std::endl;
	setActiveBody(rocket);

	forces.push_back(std::make_unique<GravityForce>(Vector2{ 0.0, -9.81 }));
	forces.push_back(std::make_unique<ThrustForce>(10'000, 0));
}

Simulation::~Simulation() {
	for (auto& [id, body] : state.bodies) {
		delete body;
	}
	state.bodies.clear();
}

void Simulation::simulateGpuDelay() {
	const int iterations = 400'000;
	volatile double result = 0.0;

	for (int i = 0; i < iterations; i++) {
		result += std::sin(i * 0.001) * std::cos(i * 0.001);
	}
}

void Simulation::step(InputState& input) {
	for (auto& [id, body] : state.bodies) {
		Vector2 netForce{ 0.0, 0.0 };
		double netTorque = 0.0;

		for (const auto& force : forces) {
			netForce += force->computeForce(*body);
			netTorque += force->computeTorque(*body);
		}

		Vector2 acceleration = netForce / body->mass;
		body->velocity += acceleration * dt;
		body->position += body->velocity * dt;

		if (input.WPressed) {
			RigidBody* rigidBody = dynamic_cast<RigidBody*>(state.activeBody);
			if (rigidBody) rigidBody->throttle = 1.0;
		}
		else if (input.SPressed) {
			RigidBody* rigidBody = dynamic_cast<RigidBody*>(state.activeBody);
			if (rigidBody) rigidBody->throttle = -1.0;
		}
		else {
			RigidBody* rigidBody = dynamic_cast<RigidBody*>(state.activeBody);
			if (rigidBody) rigidBody->throttle = 0.0;
		}

		/*double angularAcceleration = netTorque / body->momOfInertia;
		body->angularFrequency += angularAcceleration * dt;
		body->angle += body->angularFrequency * dt;*/

		/*if (count % 60 == 0) {
			std::cout << "Object: " << body.name << "\n";
			std::cout << "Net Force: (" << netForce.x << ", " << netForce.y << ")\n";
			std::cout << "Mass: " << body.mass << "\n";
			std::cout << "Moment of Inertia: " << body.momOfInertia << "\n";
			std::cout << "Position: (" << body.position.x << ", " << body.position.y << ")\n";
			std::cout << "Velocity: (" << body.velocity.x << ", " << body.velocity.y << ")\n";
			std::cout << "Acceleration: (" << acceleration.x << ", " << acceleration.y << ")\n";
			std::cout << "Rotation: " << (body.angle * 180 / 3.1415926535) << "\n";
			std::cout << "dt: " << dt << "\n";
			std::cout << "-------------------\n";
		}*/

		state.time += dt;
	}

	//simulateGpuDelay();
}

const WorldState& Simulation::getState() const {
	return state;
}

void Simulation::setActiveBody(Body* body) {
	if (state.activeBody) {
		state.activeBody->isActive = false;
		state.activeBody->colour = White;
	}
	state.activeBody = body;
	if (state.activeBody) {
		state.activeBody->isActive = true;
		state.activeBody->colour = Red;
	} else {
		std::cout << "No active body set" << std::endl;
	}
}