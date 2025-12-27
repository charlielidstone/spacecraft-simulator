#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation/Simulation.hpp"
#include <iomanip>

int main(void) {

	constexpr auto WINDOW_WIDTH = 800;
	constexpr auto WINDOW_HEIGHT = 600;

	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Spacecraft Simulator");

	constexpr double SIM_FREQ_HZ = 120.0;

	double timestep = (1 / SIM_FREQ_HZ);
	Simulation sim(timestep);

	const WorldState& state = sim.getState();

	constexpr auto ROCKET_RADIUS = 5.0F;
	sf::CircleShape rocket(ROCKET_RADIUS);
	rocket.setFillColor(sf::Color::White);

	std::cout
		<< "t = " << std::fixed << std::setprecision(4) << state.time
		<< ", y = " << state.body.position.y
		<< ", Vy = " << state.body.velocity.y
		<< std::endl;

	for (int i = 0; i < (5/timestep); i++) {
		sim.step();
		const WorldState& state = sim.getState();

		std::cout
			<< "t = " << std::fixed << std::setprecision(4) << state.time
			<< ", y = " << state.body.position.y
			<< ", Vy = " << state.body.velocity.y
			<< std::endl;
	}

	/*while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		sim.step();

		const WorldState& state = sim.getState();

		rocket.setPosition({
			static_cast<float>(state.body.position.x),
			static_cast<float>(WINDOW_HEIGHT - state.body.position.y)
		});

		window.clear();
		window.draw(rocket);
		window.display();
	}*/

	return 0;
}