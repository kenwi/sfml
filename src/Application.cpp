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
						view.zoom(zoomLevel *= 0.9f);
						window.setView(view);

						std::cout << "Zoom-- " << zoomLevel << std::endl;
					}

					if (event.key.code == sf::Keyboard::Down)
					{
						sf::View view = window.getDefaultView();
						view.zoom(zoomLevel *= 1.1f);
						window.setView(view);

						std::cout << "Zoom++ " << zoomLevel << std::endl;
					}
				}
			}
			
			sf::Time elapsed = clock.restart();
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			ship.update(elapsed);
			
			sf::Vector2f p((float)mouse.x, (float)mouse.y);
			sf::Vector2f p0 = earth.getCenter();

			float altitude = (float)sqrt(pow(p.x - p0.x, 2.0f) + pow(p.y - p0.y, 2.0f)) - earth.getRadius();

			float density = earth.getAltitudeDensity(altitude);
			float a = clamp<float>(density, 0.0f, 1.0f);

			sf::Color blue(sf::Color::Blue);
			sf::Color black(sf::Color::Black);

			float r = blue.r * a + (black.r * (1.0f - a));
			float g = blue.g * a + (black.g * (1.0f - a));
			float b = blue.b * a + (black.b * (1.0f - a));

			cout << "altitude=" << altitude << " alpha=" << density  << " ac=" << a << endl;

			window.clear(sf::Color(r, g, b));
			window.draw(ship);
			window.draw(earth);
			
			window.display();
		}

		std::cout << "Release application";

		return 0;
	}
}
