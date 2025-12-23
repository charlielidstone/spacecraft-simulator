#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "../state/WorldState.hpp"

class Simulation {
	public:
		Simulation(double timestep);

		void step();
		const WorldState& getState() const;
	
	private:
		double dt;
		WorldState state;
};

#endif