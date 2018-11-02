#pragma once

#include <imgui.h>
#include <imgui-SFML.h>

#include "Application.hpp"
#include "ParticleSystem.hpp"
#include "Grid.hpp"
#include "Ship.hpp"
#include "World.hpp"

using namespace std;

namespace Game
{
	int Application::Run()
	{
		cout << "Start application" << endl;

		GWorld world;
		Clock clock;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed
					|| event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}			
			sf::Time elapsed = clock.restart();
			sf::Vector2i mouse = sf::Mouse::getPosition(window);

			world.update(elapsed.asSeconds());
			
			window.clear();
			for (sf::Drawable* o : world.getDrawQueue())
				window.draw(*o);
			window.display();
		}
		
		std::cout << "Release application";
		return 0;
	}
}