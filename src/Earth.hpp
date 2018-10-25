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

	Earth(const float radius, const sf::Vector2f initialPosition)
	{
		this->radius = radius;

		shape.setRadius(radius);
		shape.setOutlineColor(sf::Color(35, 38, 34)); // Black-ish
		shape.setFillColor(sf::Color(16, 160, 6));	  // Green-ish
		shape.setOutlineThickness(2);
		shape.setPointCount(200);

		setCenterAt(initialPosition.x, initialPosition.y);
	}

	void setCenterAt(float x, float y)
	{
		x -= radius;
		y -= radius;
		shape.setPosition(sf::Vector2f(x, y));
	}

private:
	float radius;
	sf::CircleShape shape;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(shape, states);
	}
};