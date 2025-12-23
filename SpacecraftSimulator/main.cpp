#include <iostream>
#include "simulation/Simulation.hpp"


int main(void) {

	double timestep = (1 / 60.0);
	Simulation sim(timestep);

	for (int i = 0; i < 300; i++) {
		sim.step();
		const auto& state = sim.getState();

		std::cout
			<< "t = " << state.time
			<< ", y = " << state.body.position.y
			<< ", Vy = " << state.body.velocity.y
			<< std::endl;
	}

	return 0;
}