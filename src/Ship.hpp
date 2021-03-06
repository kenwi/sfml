#pragma once

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
		: radius(5)
		, earth(earth)
		, velocity(0.0f, 0.0f)
		, totalTime(0)
	{
		shape.setRadius(radius);
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineThickness(1);
		shape.setOutlineColor(sf::Color(35, 38, 34));
		setCenterAt(initialPosition.x, initialPosition.y);
	}

	void resetTo(float x, float y)
	{
		velocity = sf::Vector2f(0.0f, 0.0f);
		setCenterAt(x, y);
	}

	sf::Vector2f getCenter()
	{
		sf::Vector2f position = shape.getPosition();
		return sf::Vector2f(position.x + radius, position.y + radius);
	}

	void setCenterAt(float x, float y)
	{
		shape.setPosition(sf::Vector2f(x - radius, y - radius));
	}

	void update(sf::Time deltaTime)
	{
		sf::Vector2f position = getCenter();
		float height = earth.getHeightAboveGround(position) - radius;
		
		float speed = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
		cout << "speed " << speed << endl;

		float drag = earth.CalculateDrag(speed, height, radius);
		//cout << "drag " << drag << endl;

		sf::Vector2f gravity(0.0f, earth.getGravityAtHeight(height));
		gravity = sf::Vector2f(pow(gravity.x, 2) / 1000, pow(gravity.y, 2) / 1000);

		if (height <= 0)
		{
			velocity.x = -abs(velocity.x);
			velocity.y = -abs(velocity.y);
		}
		velocity.y += gravity.y - (2.0f * sqrt(speed) * 0.01f);
		position += velocity * deltaTime.asSeconds();

		setCenterAt(position.x, position.y);
		totalTime += deltaTime.asSeconds();
	}

private:
	float radius;
	sf::CircleShape shape;
	sf::Vector2f velocity;
	Earth earth;
	float totalTime;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(shape, states);
	}
};