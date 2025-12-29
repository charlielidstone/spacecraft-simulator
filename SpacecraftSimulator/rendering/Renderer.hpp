#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../math/Vector2.hpp"
#include "../state/WorldState.hpp"
#include <SFML/Graphics.hpp>

class Renderer {
	public:
		sf::RenderWindow window;

		Renderer()
			: window(sf::VideoMode({ 800, 600 }), "Spacecraft Simulator"), scale(1.0), accumulator(0.0)
		{}

		void setup() {
			marker1.setSize(sf::Vector2f(1.0, 20.0));
			marker1.setFillColor(sf::Color::Red);
			marker1.setPosition({ sf::Vector2f(static_cast<float>(origin.x), static_cast<float>(origin.y)) });
			
			marker2.setSize(sf::Vector2f(1.0, 20.0));
			marker2.setFillColor(sf::Color::Blue);
			marker2.setPosition({ sf::Vector2f(static_cast<float>(origin.x + 305.81039), static_cast<float>(origin.y)) });

			constexpr auto ROCKET_RADIUS = 5.0F;
			rocket.setRadius(ROCKET_RADIUS);
			rocket.setFillColor(sf::Color::White);

			// set origin of all shapes to center of shape
			rocket.setOrigin(sf::Vector2f(ROCKET_RADIUS, ROCKET_RADIUS));
			marker1.setOrigin(sf::Vector2f(0.5F, 10.0F));
			marker2.setOrigin(sf::Vector2f(0.5F, 10.0F));
		}

		void render(const WorldState& state) {
			rocket.setPosition({
				static_cast<float>(origin.x + state.body.position.x),
				static_cast<float>(origin.y - state.body.position.y)
			});

			window.clear();
			window.draw(rocket);
			window.draw(marker1);
			window.draw(marker2);
			window.display();
		}

		double consumeFrameTime() {
			return frameClock.restart().asSeconds();
		}

		void handleWindowEvents() {
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
			}
		}

	private:
		// @brief At scale = 1, 1 unit in simulation space = 1 SFML unit
		double scale;
		const int WINDOW_WIDTH = 800;
		const int WINDOW_HEIGHT = 600;
		const Vector2 origin = { WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0 };
		sf::Clock frameClock;
		double accumulator;
		
		// these are hardcoded for now, but we will store them as a list later
		sf::CircleShape rocket;
		sf::RectangleShape marker1;
		sf::RectangleShape marker2;
};

#endif