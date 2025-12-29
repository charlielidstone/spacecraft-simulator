#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../simulation/Simulation.hpp"
#include "../rendering/Renderer.hpp"
#include "InputState.hpp"

class Application {
	public:
		Application();

		void setup();
		void run();

		InputState& getInput(); // this will need to be moved

	private:
		double sim_freq;
		Simulation simulation;
		Renderer renderer;
};

#endif