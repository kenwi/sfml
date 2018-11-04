#pragma once

#include <imgui.h>
#include <imgui-SFML.h>

#include "Application.hpp"
#include "ParticleSystem.hpp"
#include "Grid.hpp"
#include "Ship.hpp"
#include "World.hpp"
#include "InputComponent.hpp"

using namespace std;

namespace Game
{
	int Application::Run()
	{
		cout << "Start application" << endl;

		GWorld world(window);
		InputComponent input(window);
		Clock clock;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				input.update(event);
			}			
			sf::Time elapsed = clock.restart();
			sf::Vector2i mouse = sf::Mouse::getPosition(window);

			world.update(elapsed.asSeconds());
			
			window.clear();
			for (sf::Drawable* o : world.getDrawQueue())
				window.draw(*o);
			window.display();
		}
		
		std::cout << "Release application" << std::endl;
		return 0;
	}
}