#include "Application.hpp"
#include "ParticleSystem.hpp"
#include "Grid.hpp"
#include "Ship.hpp"

using namespace std;

namespace Game
{
    int Application::Run()
    {
        int WindowWidth = 640, WindowHeight = 480;        
        cout << "Start application" << endl;
        
        auto  style = sf::Style::Titlebar | sf::Style::Close;// | sf::Style::Fullscreen;
        sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Game", style);

        float HeightAboveGround = 50;
        float EarthRadius = 5000;

        sf::Vector2f EarthPosition(WindowWidth/2, WindowHeight + EarthRadius - HeightAboveGround);
        Earth earth(EarthRadius, EarthPosition);

        //y + windowHeight + EarthRadius =  + HeightAboveGround

        Ship ship(sf::Vector2f(WindowWidth/2, WindowHeight/2), earth);

        ParticleSystem particles(10000);

        sf::Clock clock;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }

                    if(event.key.code == sf::Keyboard::Space)
                    {
                        ship.resetPosition(WindowWidth/2, 0);
                    }

                    if(event.key.code == sf::Keyboard::BackSpace)
                    {
                        style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen;
                        window.create(sf::VideoMode(WindowWidth, WindowHeight), "Game", style);
                    }
                }
            }

            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            
            sf::Time elapsed = clock.restart();
            ship.update(elapsed);

            //particles.setEmitter(window.mapPixelToCoords(mouse));
            //particles.update(elapsed);

            window.clear(sf::Color(140, 140, 140));            
            window.draw(ship);            
            window.draw(earth);
            //window.draw(particles);
            window.display();
        }
        
        std::cout << "Release application";

        return 0;
    }
}
