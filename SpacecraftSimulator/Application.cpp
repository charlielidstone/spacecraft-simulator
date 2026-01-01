#include "application/Application.hpp"
#include <SFML/Graphics.hpp>

Application::Application() : sim_freq(120.0), simulation(1.0 / sim_freq), renderer() {}

void Application::setup() {
	const WorldState& initialState = simulation.getState();
	renderer.setup(initialState);
}

void Application::run() {
	double accumulator = 0.0;
	double frameTime = 0.0;

	while (renderer.window.isOpen()) {
		frameTime = renderer.consumeFrameTime();
		accumulator += frameTime;

		while (accumulator >= (1 / sim_freq)) {
			std::cout << "Physics behind real-time by: " << accumulator << " seconds" << std::endl;
			InputState& input = getInput();
			simulation.step(input);
			accumulator -= (1 / sim_freq);

			if (renderer.handleWindowEvents()) break;
		}

		const WorldState& state = simulation.getState();
		renderer.render(state);
	}
}

InputState& Application::getInput() {
	InputState input{};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
		input.shiftPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		input.WPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		input.SPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		input.APressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		input.DPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		input.LeftArrowPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		input.RightArrowPressed = true;
	}

	return input;
}