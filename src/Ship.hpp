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
		: radius(10)
		, earth(earth)
		, velocity(0.0f, 0.0f)
	{
		shape.setRadius(radius);
		shape.setFillColor(sf::Color::Red);

		setCenterAt(initialPosition.x, initialPosition.y);
	}

	void resetTo(float x, float y)
	{
		velocity = sf::Vector2f(0.0f, 0.0f);
		setCenterAt(x, y);
	}

	void setCenterAt(float x, float y)
	{
		x -= radius;
		y -= radius;
		center.x = x;
		center.y = y;
		shape.setPosition(sf::Vector2f(x, y));
	}

	void update(sf::Time deltaTime)
	{
		sf::Vector2f position = shape.getPosition();
		sf::Vector2f gravity(0.0f, -9.81f);

		float height = earth.getHeightAboveGround(sf::Vector2f(position.x, position.y + radius));
		std::cout << height << std::endl;

		if (height <= 0)
		{
			velocity.x = -abs(velocity.x);
			velocity.y = -abs(velocity.y);
		}

		velocity.x += gravity.x * gravity.x / 1000;
		velocity.y += gravity.y * gravity.y / 1000;

		position += velocity * deltaTime.asSeconds();

		shape.setPosition(position.x, position.y);
	}

private:
	float radius;
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f center;
	Earth earth;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(shape, states);
	}
};