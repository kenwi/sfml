#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <iostream>

class Earth : public sf::Drawable, public sf::Transformable
{
public:
  Earth() 
  {
    Earth(1, sf::Vector2f(0.0f, 0.0f));
  }
  
  Earth(float radius, sf::Vector2f initialPosition)
  {
    this->position = initialPosition;
    this->radius = radius;
    
    shape.setRadius(radius);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::Green);    
    shape.setOutlineThickness(2);
    shape.setPosition(position);
    shape.setPointCount(200);

    resetPosition(position.x, position.y);
  }

  void resetPosition(float x, float y)
  {
    position = sf::Vector2f(x, y);

    position.x -= radius;
    position.y -= radius;
    
    shape.setPosition(position);
  }

private:
  float radius;
  sf::Vector2f position;
  sf::CircleShape shape;

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
  {
    states.transform *= getTransform();
    states.texture = NULL;
    target.draw(shape, states);
  }
};