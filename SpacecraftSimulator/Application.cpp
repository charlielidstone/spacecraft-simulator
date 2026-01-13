#include "application/Application.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

Application::Application() : sim_freq(120.0), simulation(1.0 / sim_freq), renderer() {}

void Application::setup() {
	const WorldState& initialState = simulation.getState();
	renderer.setup(initialState);
}

void Application::run() {
	double accumulator = 0.0;
	double frameTime = 0.0;

	while (renderer.window.isOpen()) {
		auto frameStart = std::chrono::high_resolution_clock::now();
		
		frameTime = renderer.consumeFrameTime();
		accumulator += frameTime;

		while (accumulator >= (1 / sim_freq)) {
			std::cout << "-------------------\n";
			std::cout << "Frame time: " << frameTime << " seconds\n";
			std::cout << "FPS: " << 1.0 / frameTime << "\n";
			// Frame count is a somewhat misleading, it is the number of actual frames, while FPS is the number of possible frames
			std::cout << "Frame count: " << simulation.getFrameCount() << "\n";
			std::cout << "Scale: " << renderer.getScale() << "\n";

			if (getInput().DownArrowPressed) {
				sf::Vector2f currentSize = renderer.view.getSize();
				sf::Vector2f newSize = sf::Vector2f(currentSize.x + 10.f, currentSize.y + 10.f);
				renderer.view.setSize(newSize);
				renderer.window.setView(renderer.view);
			}
			else if (getInput().UpArrowPressed) {
				sf::Vector2f currentSize = renderer.view.getSize();
				sf::Vector2f newSize = sf::Vector2f( currentSize.x - 10.f, currentSize.y - 10.f);
				renderer.view.setSize(newSize);
				renderer.window.setView(renderer.view);
			}

			if (accumulator > 0.009) {
				std::cout << "Physics behind real-time by: " << accumulator << " seconds" << std::endl;
				
				// Time each operation
				auto t1 = std::chrono::high_resolution_clock::now();
				InputState& input = getInput();
				auto t2 = std::chrono::high_resolution_clock::now();
				simulation.step(input);
				auto t3 = std::chrono::high_resolution_clock::now();
				
				std::cout << "  Input: " << std::chrono::duration<double, std::milli>(t2 - t1).count() << "ms\n";
				std::cout << "  Simulation: " << std::chrono::duration<double, std::milli>(t3 - t2).count() << "ms\n";
			} else {
				InputState& input = getInput();
				simulation.step(input);
			}
			accumulator -= (1 / sim_freq);

			simulation.incrementFrameCount();

			if (renderer.handleWindowEvents()) break;
		}

		auto renderStart = std::chrono::high_resolution_clock::now();
		const WorldState& state = simulation.getState();
		renderer.render(state);
		auto renderEnd = std::chrono::high_resolution_clock::now();
		
		if (accumulator > 0.009) {
			std::cout << "  Render: " << std::chrono::duration<double, std::milli>(renderEnd - renderStart).count() << "ms\n";
		}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		input.DownArrowPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		input.UpArrowPressed = true;
	}

	return input;
}