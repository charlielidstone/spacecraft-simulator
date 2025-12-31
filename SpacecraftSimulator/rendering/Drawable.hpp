#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <cstddef>
#include <SFML/Graphics.hpp>

using ObjectID = std::size_t;

struct Drawable {
	ObjectID id;
	sf::RectangleShape object;
};

#endif