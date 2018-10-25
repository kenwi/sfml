#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Earth.hpp"

#include <iostream>

class Ship : public sf::Drawable, public sf::Transformable
{
  public:
    Ship(sf::Vector2f initialPosition, Earth &earth)
    {
        this->radius = 10;
        this->earth = earth;        
       
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);

        resetPosition(initialPosition.x, initialPosition.y);
    }

    void resetPosition(float x, float y)
    {
        velocity = sf::Vector2f(0.0f, 0.0f);
        position = sf::Vector2f(x, y);

        position.x -= radius;
        position.y -= radius;

        shape.setPosition(position);
    }

    void update(sf::Time DeltaTime)
    {
        sf::Vector2f gravity(0.0f, -9.81f);
        
        velocity.x += gravity.x * gravity.x / 1000;
        velocity.y += gravity.y * gravity.y / 1000;

        position += velocity * DeltaTime.asSeconds();        
        shape.setPosition(position);
    }

  private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    float radius;
    Earth earth;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(shape, states);
    }
};