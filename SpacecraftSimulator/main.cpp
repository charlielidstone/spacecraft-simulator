#include <iostream>
#include <SFML/Graphics.hpp>
#include "simulation/Simulation.hpp"
#include "application/Application.hpp"
#include <iomanip>

int main(void) {

	Application application;
	application.setup();
	application.run();

	return 0;
}