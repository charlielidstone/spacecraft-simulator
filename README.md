# Spacecraft Simulator

A little rocket simulator.

At this point we have a basic physics engine and a renderer which work together to move some objects around on the screen.

Setting this up in Visual Studio was kind of tedious. All the .dll files need to be placed in the same directory as the executable for it to run.

I decided not to use a whole game engine for this, so instead I'm using [SFML](https://www.sfml-dev.org/) which is a low level library to open windows and whatnot.
