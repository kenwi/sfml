#pragma once

#include <iostream>
#include "ComponentBase.hpp"


class InputComponent : ApplicationComponent
{
public:
	InputComponent(sf::RenderWindow& renderWindow)
		: ApplicationComponent(renderWindow)
	{

	}

	// Inherited via AComponent
	virtual void update(sf::Event & event) override
	{
		if (event.type == sf::Event::Closed
			|| event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			std::cout << "InputComponent received keyboard event" << std::endl;
			Quit();
		}
	};
};