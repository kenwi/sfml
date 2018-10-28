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
		float heightAboveGround = 50;
		float earthRadius = 10000;

		sf::Vector2f EarthPosition(windowCenter.x, windowCenter.y + earthRadius + heightAboveGround);
		Earth earth(earthRadius, EarthPosition);
		Ship ship(sf::Vector2f(windowCenter), earth);

		sf::Image buffer = earth.createAtmosphere(windowWidth, windowHeight, zoomLevel);
		sf::Texture texture;
		texture.loadFromImage(buffer);
		sf::Sprite atmosphere(texture);

		bool mouseDown = false;
		sf::Clock clock;
		sf::Vector2i oldMousePosition;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseWheelScrolled)
				{
					if (event.mouseWheelScroll.delta < 0)
					{
						auto view = window.getView();
						view.zoom(2);
						zoomLevel *= 2;
						window.setView(view);
						std::cout << "Zoom-- " << zoomLevel << std::endl;
					}

					if (event.mouseWheelScroll.delta > 0)
					{
						if (zoomLevel > 1)
						{
							auto view = window.getView();
							view.zoom(0.5);
							zoomLevel /= 2;
							window.setView(view);
							std::cout << "Zoom++ " << zoomLevel << std::endl;
						}
					}
				}

				if (event.type == sf::Event::MouseButtonPressed)
				{	
					const auto mousePos = sf::Mouse::getPosition();
					oldMousePosition = sf::Vector2i(mousePos.x, mousePos.y);
					mouseDown = true;

					cout << "Start scroll" << mousePos.x << " " << mousePos.y << endl;
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					cout << "Stop scroll" << endl;
					mouseDown = false;
				}

				if (event.type == sf::Event::MouseMoved)
				{
					if (mouseDown)
					{
						const auto mousePos = sf::Mouse::getPosition();
						const int dx = oldMousePosition.x - mousePos.x;
						const int dy = oldMousePosition.y - mousePos.y;

						cout << "dx=" << dx << " dy=" << dy << endl;

						auto view = window.getView();
						view.move(dx * zoomLevel, dy * zoomLevel);
						window.setView(view);

						oldMousePosition = mousePos;
					}
				}


				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) {
						window.close();
					}

					if (event.key.code == sf::Keyboard::Space)
					{
						auto view = window.getView();
						view.move(1, 0);
						window.setView(view);
					}
				}
			}
			
			sf::Time elapsed = clock.restart();
			sf::Vector2i mouse = sf::Mouse::getPosition(window);

			ship.update(elapsed);
			
			window.clear();
			window.draw(atmosphere);
			window.draw(earth);
			window.draw(ship);
			window.display();
		}

		std::cout << "Release application";

		return 0;
	}
}
