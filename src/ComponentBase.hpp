#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

// Game component
class GameComponent
{
private:

public:
	virtual void update(float deltaTime) = 0;
};

// Application component
class ApplicationComponent
{
	sf::Window *window;

public:
	ApplicationComponent(sf::Window &window)
		: window(&window)
	{

	}

	void Quit()
	{
		std::cout << "ApplicationComponent received Quit" << std::endl;
		window->close();
	}

	virtual void update(sf::Event &event) = 0;
};
