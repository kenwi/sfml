#include "Application.hpp"
#include "ParticleSystem.hpp"
#include "Grid.hpp"
#include "Ship.hpp"

using namespace std;

namespace Game
{
	int Application::Run()
	{
		cout << "Start application" << endl;

		int windowWidth = 1024, windowHeight = 768;
		sf::Vector2f windowCenter(windowWidth * 0.5f, windowHeight * 0.5f);

		auto  style = sf::Style::Titlebar | sf::Style::Close;// | sf::Style::Fullscreen;
		sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "", style);

		float heightAboveGround = 50;
		float earthRadius = 10000;

		sf::Vector2f EarthPosition(windowCenter.x, windowCenter.y + earthRadius + 100);

		Earth earth(earthRadius, EarthPosition);
		Ship ship(sf::Vector2f(windowCenter), earth);

		ParticleSystem particles(1000);

		sf::View view(windowCenter, sf::Vector2f((float)windowWidth, (float)windowHeight));
		view.setViewport(sf::FloatRect(1.0, 1.0, 1.0, 1.0));
		
		float zoomLevel = 1;
		sf::Clock clock;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}

					if (event.key.code == sf::Keyboard::Space)
					{
						ship.resetTo(windowWidth * 0.5f, 0.0f);
					}

					if (event.key.code == sf::Keyboard::Up)
					{
						sf::View view = window.getDefaultView();
						view.zoom(zoomLevel *= 0.5f);
						window.setView(view);

						std::cout << "Zoom-- " << zoomLevel << std::endl;
					}

					if (event.key.code == sf::Keyboard::Down)
					{
						sf::View view = window.getDefaultView();
						view.zoom(zoomLevel *= 2.0f);
						window.setView(view);

						std::cout << "Zoom++ " << zoomLevel << std::endl;
					}
				}
			}
			
			sf::Time elapsed = clock.restart();
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			ship.update(elapsed);

			window.clear(sf::Color(45, 130, 226));			
			window.draw(ship);
			window.draw(earth);
			
			window.display();
		}

		std::cout << "Release application";

		return 0;
	}
}
