#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../math/Vector2.hpp"
#include "../state/WorldState.hpp"
#include "../rendering/Drawable.hpp"
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <vector>

class Renderer {
	public:
		sf::RenderWindow window;
		sf::View view;

		Renderer();

		void setup(const WorldState& state);
		void render(const WorldState& state);
		double consumeFrameTime();
		int handleWindowEvents();
		double getScale();
		void setScale(double newScale);

	private:
		void generateGrid();
		void updateObject(Drawable& drawable, const RigidBody& body);

		// @brief At scale = 1, 1 unit in simulation space = 1 SFML unit
		double scale;
		const double metersPerGridSquare = 10.0; // Each grid square = 1 metre
		const int WINDOW_WIDTH = 500;
		const int WINDOW_HEIGHT = 500;
		const Vector2 origin = { WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0 };
		Vector2 relativeOrigin = origin;
		sf::Clock frameClock;
		double accumulator;
		
		std::vector<sf::RectangleShape> gridLines;
		
		// these are hardcoded for now, but we will store them as a list later
		sf::RectangleShape marker1;
		sf::RectangleShape marker2;

		std::unordered_map<ObjectID, Drawable> drawables;
};

#endif