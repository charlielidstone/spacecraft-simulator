#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation/Simulation.hpp"

int main(void) {

	constexpr auto WINDOW_WIDTH = 800;
	constexpr auto WINDOW_HEIGHT = 600;

	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Spacecraft Simulator");

	double timestep = (1 / 60.0);
	Simulation sim(timestep);

	constexpr auto ROCKET_RADIUS = 5.0F;
	sf::CircleShape rocket(ROCKET_RADIUS);
	rocket.setFillColor(sf::Color::White);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		sim.step();

		const WorldState& state = sim.getState();

		rocket.setPosition({
				static_cast<float>(state.body.position.x),
				static_cast<float>(600.0 - state.body.position.y)
			});

		window.clear();
		window.draw(rocket);
		window.display();
	}

	return 0;
}