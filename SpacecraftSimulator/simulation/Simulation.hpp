#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../state/WorldState.hpp"
#include "../physics/Force.hpp"
#include "../application/InputState.hpp"
#include <vector>
#include <memory>

class Simulation {
	public:
		Simulation(double timestep);

		void step(InputState& input);
		const WorldState& getState() const;
	
	private:
		// @brief Delta time, used for Euler integration
		double dt;
		WorldState state;
		std::vector<std::unique_ptr<Force>> forces;
		int count = 0;

		void simulateGpuDelay();
};

#endif