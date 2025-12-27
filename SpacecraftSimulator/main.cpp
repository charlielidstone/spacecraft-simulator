#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation/Simulation.hpp"
#include <iomanip>

int main(void) {

	constexpr auto WINDOW_WIDTH = 800;
	constexpr auto WINDOW_HEIGHT = 600;

	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Spacecraft Simulator");

	const Vector2 ORIGIN = { WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0 };

	constexpr double SIM_FREQ_HZ = 120.0;

	double timestep = (1 / SIM_FREQ_HZ);
	Simulation sim(timestep);

	const WorldState& state = sim.getState();

	sf::RectangleShape marker1(sf::Vector2f(1.0, 20.0));
	marker1.setFillColor(sf::Color::Red);
	marker1.setPosition({ sf::Vector2f(static_cast<float>(ORIGIN.x), static_cast<float>(ORIGIN.y)) });
	sf::RectangleShape marker2(sf::Vector2f(1.0, 20.0));
	marker2.setFillColor(sf::Color::Blue);
	marker2.setPosition({ sf::Vector2f(static_cast<float>(ORIGIN.x + 305.81039), static_cast<float>(ORIGIN.y)) });

	constexpr auto ROCKET_RADIUS = 5.0F;
	sf::CircleShape rocket(ROCKET_RADIUS);
	rocket.setFillColor(sf::Color::White);

	sf::Clock delayClock;
	constexpr float DELAY_SECONDS = 2.0f;
	bool simulationStarted = false;

	// set origin of all shapes to center
	rocket.setOrigin(sf::Vector2f(ROCKET_RADIUS, ROCKET_RADIUS));
	marker1.setOrigin(sf::Vector2f(0.5F, 10.0F));
	marker2.setOrigin(sf::Vector2f(0.5F, 10.0F));

	sf::Clock frameClock;
	double accumulator = 0.0;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		if (!simulationStarted && delayClock.getElapsedTime().asSeconds() >= DELAY_SECONDS) {
			simulationStarted = true;
		}

		if (simulationStarted) {
			double frameTime = frameClock.restart().asSeconds();
			std::cout << "Frame Time: " << std::fixed << std::setprecision(4) << frameTime << " seconds\n";

			/*if (frameTime > 0.25) {
				frameTime = 0.25;
			}*/

			accumulator += frameTime;

			while (accumulator >= timestep) {
				std::cout << "Accumulator: " << std::fixed << std::setprecision(4) << accumulator << " seconds\n";
				sim.step();
				accumulator -= timestep;
			}
		} else {
			frameClock.restart();
		}

		const WorldState& state = sim.getState();

		rocket.setPosition({
			static_cast<float>(ORIGIN.x + state.body.position.x),
			static_cast<float>(ORIGIN.y - state.body.position.y)
		});

		window.clear();
		window.draw(rocket);
		window.draw(marker1);
		window.draw(marker2);
		window.display();
	}

	return 0;
}