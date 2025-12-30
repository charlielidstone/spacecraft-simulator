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

		void setup(const WorldState& state) {
			marker1.setSize(sf::Vector2f(1.0, 20.0));
			marker1.setFillColor(sf::Color::Red);
			marker1.setPosition({ sf::Vector2f(static_cast<float>(origin.x), static_cast<float>(origin.y)) });
			
			marker2.setSize(sf::Vector2f(1.0, 20.0));
			marker2.setFillColor(sf::Color::Blue);
			marker2.setPosition({ sf::Vector2f(static_cast<float>(origin.x + 305.81039), static_cast<float>(origin.y)) });

			marker1.setOrigin(sf::Vector2f(0.5F, 10.0F));
			marker2.setOrigin(sf::Vector2f(0.5F, 10.0F));

			for (const auto& body : state.bodies) {
				objects.push_back(sf::RectangleShape());
				updateObject(objects.back(), body);
			}

			generateGrid();
		}

		void render(const WorldState& state) {
			for (int i = 0; i < state.bodies.size(); i++) {
				updateObject(objects[i], state.bodies[i]);
			}

			window.clear();
			
			for (const auto& line : gridLines) {
				window.draw(line);
			}

			window.draw(marker1);
			window.draw(marker2);

			for (const auto& object : objects) {
				window.draw(object);
			}
			
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
			
			const float gridSpacing = static_cast<float>(scale * metersPerGridSquare);
			
			const sf::Color gridColor(10, 10, 10, 255);
			
			for (float x = 0; x < WINDOW_WIDTH; x += gridSpacing) {
				sf::RectangleShape line(sf::Vector2f(1.0f, static_cast<float>(WINDOW_HEIGHT)));
				line.setPosition({ x, 0 });
				line.setFillColor(gridColor);
				gridLines.push_back(line);
			}
			
			for (float y = 0; y < WINDOW_HEIGHT; y += gridSpacing) {
				sf::RectangleShape line(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 1.0f));
				line.setPosition({ 0, y });
				line.setFillColor(gridColor);
				gridLines.push_back(line);
			}
			
			// Highlight origin lines (brighter)
			sf::RectangleShape originLineX(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 1.0f));
			originLineX.setPosition({ 0, static_cast<float>(origin.y) });
			originLineX.setFillColor(sf::Color(40, 40, 40, 255));
			gridLines.push_back(originLineX);
			
			sf::RectangleShape originLineY(sf::Vector2f(1.0f, static_cast<float>(WINDOW_HEIGHT)));
			originLineY.setPosition({ static_cast<float>(origin.x), 0 });
			originLineY.setFillColor(sf::Color(40, 40, 40, 255));
			gridLines.push_back(originLineY);
		}

		/**
		 * @brief Updates a single object based on its simulation body
		 * @param state The current world state
		 * @param index The index of the object/body to update
		 */
		void updateObject(WorldState& state, size_t index) {
			objects[index].setPosition({
				static_cast<float>(origin.x + state.bodies[index].position.x * scale),
				static_cast<float>(origin.y - state.bodies[index].position.y * scale)
			});
			objects[index].setRotation(sf::radians(state.bodies[index].angle - (std::numbers::pi / 2)));
			objects[index].setOrigin(sf::Vector2f(state.bodies[index].width / 2, state.bodies[index].height / 2));
			objects[index].setSize(sf::Vector2f(state.bodies[index].width, state.bodies[index].height));
			objects[index].setFillColor(sf::Color::White);
		}

		/**
		 * @brief Updates a single object based on its simulation body
		 * @param object the renderable object to update
		 * @param body the simulation body to base the update on
		 */
		void updateObject(sf::RectangleShape& object, const RigidBody& body) {
			object.setPosition({
				static_cast<float>(origin.x + body.position.x * scale),
				static_cast<float>(origin.y - body.position.y * scale)
			});
			object.setRotation(sf::radians(body.angle - (std::numbers::pi / 2)));
			object.setOrigin(sf::Vector2f(body.width / 2, body.height / 2));
			object.setSize(sf::Vector2f(body.width, body.height));
			object.setFillColor(sf::Color::White);
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
		sf::RectangleShape rocket;
		sf::RectangleShape marker1;
		sf::RectangleShape marker2;

		std::vector<sf::RectangleShape> objects;
};

#endif