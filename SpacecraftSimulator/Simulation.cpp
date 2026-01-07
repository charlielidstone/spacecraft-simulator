#include "simulation/Simulation.hpp"
#include "math/Vector2.hpp"
#include <iostream>
#include <cmath>
#include <chrono>

Simulation::Simulation(double timestep) : dt(timestep) {
	ObjectID nextID = 0;

	state.time = 0.0;

	RigidBody rocket = {
		.id = nextID++,
		.name = "rocket",
		.width = 10.0,
		.height = 30.0,
		.mass = 100.0,
		.velocity = { 0.0, -40.0 },
		.position = { 10.0, 50.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(rocket.id, rocket);

	RigidBody otherRocket = {
		.id = nextID++,
		.name = "otherRocket",
		.width = 30.0,
		.height = 90.0,
		.mass = 100.0,
		.velocity = { 0.0, 70.0 },
		.position = { -10.0, -30.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(otherRocket.id, otherRocket);

	RigidBody rocket3 = {
		.id = nextID++,
		.name = "rocket3",
		.width = 40.0,
		.height = 20.0,
		.mass = 100.0,
		.velocity = { 10.0, 0.0 },
		.position = { -40.0, 30.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(rocket3.id, rocket3);

	RigidBody starship = {
		.id = nextID++,
		.name = "starship",
		.width = 9.0,
		.height = 123.0,
		.mass = 5'000'000.0,
		.velocity = { 0.0, 0.0 },
		.position = { 0.0, 0.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(starship.id, starship);

	RigidBody falcon9 = {
		.id = nextID++,
		.name = "falcon9",
		.width = 3.7,
		.height = 70.0,
		.mass = 549'054.0,
		.velocity = { 0.0, 0.0 },
		.position = { 50.0, 0.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(falcon9.id, falcon9);

	RigidBody satellite = {
		.id = nextID++,
		.name = "satellite",
		.width = 2.0,
		.height = 5.0,
		.mass = 1'000.0,
		.velocity = { 20.0, 0.0 },
		.position = { 0.0, 100.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(satellite.id, satellite);

	RigidBody capsule = {
		.id = nextID++,
		.name = "capsule",
		.width = 4.0,
		.height = 8.0,
		.mass = 12'000.0,
		.velocity = { -15.0, 5.0 },
		.position = { -50.0, 50.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(capsule.id, capsule);

	RigidBody debris1 = {
		.id = nextID++,
		.name = "debris1",
		.width = 1.5,
		.height = 2.0,
		.mass = 500.0,
		.velocity = { -10.0, 15.0 },
		.position = { 30.0, -40.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(debris1.id, debris1);

	RigidBody probe = {
		.id = nextID++,
		.name = "probe",
		.width = 1.0,
		.height = 1.5,
		.mass = 750.0,
		.velocity = { 5.0, -20.0 },
		.position = { -30.0, 80.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(probe.id, probe);

	RigidBody shuttle = {
		.id = nextID++,
		.name = "shuttle",
		.width = 8.7,
		.height = 37.2,
		.mass = 78'000.0,
		.velocity = { 0.0, 25.0 },
		.position = { 70.0, -50.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(shuttle.id, shuttle);

	RigidBody booster = {
		.id = nextID++,
		.name = "booster",
		.width = 2.5,
		.height = 15.0,
		.mass = 25'000.0,
		.velocity = { -8.0, 0.0 },
		.position = { 0.0, -70.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(booster.id, booster);

	RigidBody telescope = {
		.id = nextID++,
		.name = "telescope",
		.width = 4.2,
		.height = 13.2,
		.mass = 11'110.0,
		.velocity = { 12.0, -5.0 },
		.position = { -80.0, 60.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(telescope.id, telescope);

	RigidBody lander = {
		.id = nextID++,
		.name = "lander",
		.width = 4.5,
		.height = 7.0,
		.mass = 15'000.0,
		.velocity = { 0.0, -12.0 },
		.position = { 40.0, 90.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(lander.id, lander);

	RigidBody module = {
		.id = nextID++,
		.name = "module",
		.width = 6.0,
		.height = 10.0,
		.mass = 20'000.0,
		.velocity = { 18.0, 8.0 },
		.position = { -60.0, -80.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(module.id, module);

	RigidBody cargo = {
		.id = nextID++,
		.name = "cargo",
		.width = 5.0,
		.height = 12.0,
		.mass = 18'500.0,
		.velocity = { -20.0, -10.0 },
		.position = { 90.0, 20.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(cargo.id, cargo);

	RigidBody debris2 = {
		.id = nextID++,
		.name = "debris2",
		.width = 0.8,
		.height = 1.2,
		.mass = 300.0,
		.velocity = { 25.0, -18.0 },
		.position = { -90.0, -60.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(debris2.id, debris2);

	RigidBody station = {
		.id = nextID++,
		.name = "station",
		.width = 15.0,
		.height = 20.0,
		.mass = 420'000.0,
		.velocity = { 0.0, 0.0 },
		.position = { -100.0, 100.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(station.id, station);

	RigidBody hauler = {
		.id = nextID++,
		.name = "hauler",
		.width = 7.5,
		.height = 18.0,
		.mass = 32'000.0,
		.velocity = { -12.0, 6.0 },
		.position = { 110.0, -30.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(hauler.id, hauler);

	RigidBody drone = {
		.id = nextID++,
		.name = "drone",
		.width = 0.5,
		.height = 0.8,
		.mass = 150.0,
		.velocity = { 30.0, -25.0 },
		.position = { -110.0, 40.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(drone.id, drone);

	RigidBody transport = {
		.id = nextID++,
		.name = "transport",
		.width = 12.0,
		.height = 25.0,
		.mass = 85'000.0,
		.velocity = { 8.0, -15.0 },
		.position = { 60.0, 120.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(transport.id, transport);

	RigidBody debris3 = {
		.id = nextID++,
		.name = "debris3",
		.width = 1.2,
		.height = 1.8,
		.mass = 400.0,
		.velocity = { -22.0, 12.0 },
		.position = { -120.0, -90.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(debris3.id, debris3);

	RigidBody cruiser = {
		.id = nextID++,
		.name = "cruiser",
		.width = 10.5,
		.height = 32.0,
		.mass = 125'000.0,
		.velocity = { 5.0, 10.0 },
		.position = { 130.0, 70.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(cruiser.id, cruiser);

	RigidBody freighter = {
		.id = nextID++,
		.name = "freighter",
		.width = 14.0,
		.height = 28.0,
		.mass = 95'000.0,
		.velocity = { -6.0, -8.0 },
		.position = { -130.0, 110.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(freighter.id, freighter);

	RigidBody observer = {
		.id = nextID++,
		.name = "observer",
		.width = 3.0,
		.height = 6.0,
		.mass = 5'500.0,
		.velocity = { 15.0, -8.0 },
		.position = { 80.0, -110.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(observer.id, observer);

	RigidBody debris4 = {
		.id = nextID++,
		.name = "debris4",
		.width = 0.6,
		.height = 0.9,
		.mass = 200.0,
		.velocity = { -28.0, 20.0 },
		.position = { -80.0, -120.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(debris4.id, debris4);

	RigidBody interceptor = {
		.id = nextID++,
		.name = "interceptor",
		.width = 5.5,
		.height = 14.0,
		.mass = 22'000.0,
		.velocity = { 35.0, 5.0 },
		.position = { 140.0, -80.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(interceptor.id, interceptor);

	RigidBody tanker = {
		.id = nextID++,
		.name = "tanker",
		.width = 11.0,
		.height = 30.0,
		.mass = 110'000.0,
		.velocity = { -10.0, 12.0 },
		.position = { -140.0, 80.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(tanker.id, tanker);

	RigidBody relay = {
		.id = nextID++,
		.name = "relay",
		.width = 2.5,
		.height = 4.0,
		.mass = 3'000.0,
		.velocity = { 18.0, -22.0 },
		.position = { 100.0, 130.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(relay.id, relay);

	RigidBody miner = {
		.id = nextID++,
		.name = "miner",
		.width = 8.0,
		.height = 16.0,
		.mass = 45'000.0,
		.velocity = { -14.0, -16.0 },
		.position = { -100.0, -130.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(miner.id, miner);

	RigidBody scout = {
		.id = nextID++,
		.name = "scout",
		.width = 3.5,
		.height = 8.5,
		.mass = 8'000.0,
		.velocity = { 40.0, -12.0 },
		.position = { 150.0, 50.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(scout.id, scout);

	RigidBody debris5 = {
		.id = nextID++,
		.name = "debris5",
		.width = 1.0,
		.height = 1.5,
		.mass = 350.0,
		.velocity = { -32.0, 18.0 },
		.position = { -150.0, -50.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(debris5.id, debris5);

	RigidBody corvette = {
		.id = nextID++,
		.name = "corvette",
		.width = 6.5,
		.height = 19.0,
		.mass = 35'000.0,
		.velocity = { 12.0, 20.0 },
		.position = { 120.0, -120.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(corvette.id, corvette);

	RigidBody carrier = {
		.id = nextID++,
		.name = "carrier",
		.width = 20.0,
		.height = 45.0,
		.mass = 350'000.0,
		.velocity = { -4.0, 6.0 },
		.position = { -120.0, 120.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(carrier.id, carrier);

	RigidBody refinery = {
		.id = nextID++,
		.name = "refinery",
		.width = 18.0,
		.height = 35.0,
		.mass = 280'000.0,
		.velocity = { 0.0, 0.0 },
		.position = { 160.0, 0.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(refinery.id, refinery);

	RigidBody tug = {
		.id = nextID++,
		.name = "tug",
		.width = 4.5,
		.height = 9.0,
		.mass = 16'000.0,
		.velocity = { -18.0, -14.0 },
		.position = { -160.0, 0.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(tug.id, tug);

	RigidBody beacon = {
		.id = nextID++,
		.name = "beacon",
		.width = 1.5,
		.height = 3.0,
		.mass = 2'000.0,
		.velocity = { 25.0, 15.0 },
		.position = { 0.0, 160.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(beacon.id, beacon);

	RigidBody debris6 = {
		.id = nextID++,
		.name = "debris6",
		.width = 0.7,
		.height = 1.0,
		.mass = 250.0,
		.velocity = { -35.0, -22.0 },
		.position = { 0.0, -160.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(debris6.id, debris6);

	RigidBody liner = {
		.id = nextID++,
		.name = "liner",
		.width = 13.0,
		.height = 40.0,
		.mass = 150'000.0,
		.velocity = { 8.0, 10.0 },
		.position = { 170.0, 90.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(liner.id, liner);

	RigidBody constructor = {
		.id = nextID++,
		.name = "constructor",
		.width = 16.0,
		.height = 22.0,
		.mass = 200'000.0,
		.velocity = { -7.0, -9.0 },
		.position = { -170.0, -90.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(constructor.id, constructor);

	RigidBody surveyor = {
		.id = nextID++,
		.name = "surveyor",
		.width = 3.2,
		.height = 7.5,
		.mass = 6'500.0,
		.velocity = { 22.0, -16.0 },
		.position = { 145.0, -145.0 },
		.throttle = 0.0
	};

	state.bodies.emplace(surveyor.id, surveyor);

	std::cout << "Number of objects: " << nextID << std::endl;

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

		double angularAcceleration = netTorque / body.momOfInertia;
		body.angularFrequency += angularAcceleration * dt;
		body.angle += body.angularFrequency * dt;

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

void Simulation::setActiveBody(RigidBody* body) {
	if (activeBody) activeBody->isActive = false;
	activeBody = body;
	if (activeBody) {
		activeBody->isActive = true;
	} else {
		std::cout << "No active body set" << std::endl;
	}
}