#include "rendering/Renderer.hpp"
#include <iostream>
#include <numbers>

Renderer::Renderer() : scale(1.0), accumulator(0.0) {
	window = sf::RenderWindow(sf::VideoMode({ static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT) }), "Spacecraft Simulator");
	//view = sf::View(sf::FloatRect({ 100.f, 100.f }, { 600.f, 600.f }));
	view = sf::View({ 250.f, 250.f }, { 600.f, 600.f });
	view.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));
	window.setView(view);
}

void Renderer::setup(const WorldState& state) {
	marker1.setSize(sf::Vector2f(1.0, 20.0));
	marker1.setFillColor(sf::Color::Red);
	marker1.setPosition({ sf::Vector2f(static_cast<float>(relativeOrigin.x), static_cast<float>(relativeOrigin.y)) });
	
	marker2.setSize(sf::Vector2f(1.0, 20.0));
	marker2.setFillColor(sf::Color::Blue);
	marker2.setPosition({ sf::Vector2f(static_cast<float>(relativeOrigin.x + 305.81039), static_cast<float>(relativeOrigin.y)) });

	marker1.setOrigin(sf::Vector2f(0.5F, 10.0F));
	marker2.setOrigin(sf::Vector2f(0.5F, 10.0F));

	drawables.clear();
	int i = 0;
	for (auto& [key, body] : state.bodies) {
		drawables.emplace(body->id, Drawable(body->id, sf::RectangleShape{}));
		if (drawables.find(body->id) == drawables.end()) {
			std::cout << "Error creating drawable for body ID " << body->id << std::endl;
			continue;
		}
		drawables.find(body->id)->second.object.setSize(sf::Vector2f(body->width, body->height));
		updateObject(drawables.find(body->id)->second, *body);
		i++;
	}

	generateGrid();
}

void Renderer::render(const WorldState& state) {
	for (const auto& [key, body] : state.bodies) {
		auto it = drawables.find(body->id);
		//if (it != drawables.end() && !body->isActive) {
		if (it != drawables.end()) {
			updateObject(it->second, *body);
		}
	}

	//relativeOrigin = origin + state.activeBody->position;	

	window.clear();
	
	for (const auto& line : gridLines) {
		window.draw(line);
	}

	window.draw(marker1);
	window.draw(marker2);

	for (const auto& [id, drawable] : drawables) {
		window.draw(drawable.object);
	}
	
	window.display();
}

double Renderer::consumeFrameTime() {
	return frameClock.restart().asSeconds();
}

int Renderer::handleWindowEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
			return 1;
		}
	}
	return 0;
}

double Renderer::getScale() {
	return scale;
}

void Renderer::setScale(double newScale) {
	scale = newScale;
}

void Renderer::generateGrid() {
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
	
	sf::RectangleShape originLineX(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 1.0f));
	originLineX.setPosition({ 0, static_cast<float>(relativeOrigin.y) });
	originLineX.setFillColor(sf::Color(40, 40, 40, 255));
	gridLines.push_back(originLineX);
	
	sf::RectangleShape originLineY(sf::Vector2f(1.0f, static_cast<float>(WINDOW_HEIGHT)));
	originLineY.setPosition({ static_cast<float>(relativeOrigin.x), 0 });
	originLineY.setFillColor(sf::Color(40, 40, 40, 255));
	gridLines.push_back(originLineY);

	sf::RectangleShape borderTop(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 2.0f));
	borderTop.setPosition({ 0, 0 });
	borderTop.setFillColor(sf::Color::Red);
	gridLines.push_back(borderTop);
	
	sf::RectangleShape borderBottom(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), 2.0f));
	borderBottom.setPosition({ 0, static_cast<float>(WINDOW_HEIGHT - 2) });
	borderBottom.setFillColor(sf::Color::Red);
	gridLines.push_back(borderBottom);
	
	sf::RectangleShape borderLeft(sf::Vector2f(2.0f, static_cast<float>(WINDOW_HEIGHT)));
	borderLeft.setPosition({ 0, 0 });
	borderLeft.setFillColor(sf::Color::Red);
	gridLines.push_back(borderLeft);
	
	sf::RectangleShape borderRight(sf::Vector2f(2.0f, static_cast<float>(WINDOW_HEIGHT)));
	borderRight.setPosition({ static_cast<float>(WINDOW_WIDTH - 2), 0 });
	borderRight.setFillColor(sf::Color::Red);
	gridLines.push_back(borderRight);
}

void Renderer::updateObject(Drawable& drawable, const RigidBody& body) {
	drawable.object.setPosition({
		static_cast<float>(relativeOrigin.x + body.position.x * scale),
		static_cast<float>(relativeOrigin.y - body.position.y * scale)
	});
	drawable.object.setRotation(sf::radians(body.angle - (std::numbers::pi / 2)));
	drawable.object.setOrigin(sf::Vector2f(body.width / 2, body.height / 2));
	drawable.object.setSize(sf::Vector2f(body.width * scale, body.height * scale));

	if (body.colour == Red) {
		drawable.object.setFillColor(sf::Color::Red);
	} else {
		drawable.object.setFillColor(sf::Color::White);
	}
}