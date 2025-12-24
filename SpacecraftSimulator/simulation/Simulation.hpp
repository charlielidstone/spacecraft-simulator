#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../state/WorldState.hpp"
#include "../physics/Force.hpp"
#include <vector>
#include <memory>

class Simulation {
	public:
		Simulation(double timestep);

		void step();
		const WorldState& getState() const;
	
	private:
		// @brief Delta time, used for Euler integration
		double dt;
		WorldState state;
		std::vector<std::unique_ptr<Force>> forces;
};

#endif