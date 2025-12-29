#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "../simulation/Simulation.hpp"
#include "../rendering/Renderer.hpp"

class Application {
	public:
		Application()
			: sim_freq(120.0), simulation(1.0 / sim_freq), renderer()
		{}

		void setup() {
			renderer.setup();
		}

		void run() {
			double accumulator = 0.0;
			double frameTime = 0.0;

			while (renderer.window.isOpen()) {
				renderer.handleWindowEvents();

				frameTime = renderer.consumeFrameTime();
				accumulator += frameTime;

				while (accumulator >= (1 / sim_freq)) {
					simulation.step();
					accumulator -= (1 / sim_freq);
				}

				const WorldState& state = simulation.getState();
				renderer.render(state);
			}
		}

	private:
		double sim_freq;
		Simulation simulation;
		Renderer renderer;
};

#endif