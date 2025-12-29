#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../math/Vector2.hpp"
#include "../state/WorldState.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

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

			// Generate grid lines
			generateGrid();
		}

		void render(const WorldState& state) {
			rocket.setPosition({
				static_cast<float>(origin.x + state.body.position.x * scale),
				static_cast<float>(origin.y - state.body.position.y * scale)
			});

			window.clear();
			
			// Draw grid first (background)
			for (const auto& line : gridLines) {
				window.draw(line);
			}
			
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
		void generateGrid() {
			gridLines.clear();
			
			// Grid spacing in pixels (1 metre = gridSpacing pixels)
			const float gridSpacing = static_cast<float>(scale * metersPerGridSquare);
			
			// Grid color (dark gray, semi-transparent)
			const sf::Color gridColor(80, 80, 80, 255);
			
			// Vertical lines
			for (float x = 0; x < WINDOW_WIDTH; x += gridSpacing) {
				sf::RectangleShape line(sf::Vector2f(1.0f, static_cast<float>(WINDOW_HEIGHT)));
				line.setPosition({ x, 0 });
				line.setFillColor(gridColor);
				gridLines.push_back(line);
			}
			
			// Horizontal lines
			for (float y = 0; y < WINDOW_HEIGHT; y += gridSpacing) {
				sf::RectangleShape line(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 1.0f));
				line.setPosition({ 0, y });
				line.setFillColor(gridColor);
				gridLines.push_back(line);
			}
			
			// Highlight origin lines (brighter)
			sf::RectangleShape originLineX(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 1.0f));
			originLineX.setPosition({ 0, static_cast<float>(origin.y) });
			originLineX.setFillColor(sf::Color(120, 120, 120, 255));
			gridLines.push_back(originLineX);
			
			sf::RectangleShape originLineY(sf::Vector2f(1.0f, static_cast<float>(WINDOW_HEIGHT)));
			originLineY.setPosition({ static_cast<float>(origin.x), 0 });
			originLineY.setFillColor(sf::Color(120, 120, 120, 255));
			gridLines.push_back(originLineY);
		}

		// @brief At scale = 1, 1 unit in simulation space = 1 SFML unit
		double scale;
		const double metersPerGridSquare = 10.0; // Each grid square = 1 metre
		const int WINDOW_WIDTH = 800;
		const int WINDOW_HEIGHT = 600;
		const Vector2 origin = { WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0 };
		sf::Clock frameClock;
		double accumulator;
		
		std::vector<sf::RectangleShape> gridLines;
		
		// these are hardcoded for now, but we will store them as a list later
		sf::CircleShape rocket;
		sf::RectangleShape marker1;
		sf::RectangleShape marker2;
};

#endif