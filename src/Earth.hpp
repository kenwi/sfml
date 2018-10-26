#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <iostream>
#include <cmath>

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
		shape.setPointCount(400);

		setCenterAt(initialPosition.x, initialPosition.y);
	}

	float getHeightAboveGround(float x, float y)
	{
		return getHeightAboveGround(sf::Vector2f(x, y));
	}

	float getHeightAboveGround(sf::Vector2f p)
	{
		sf::Vector2f p0 = getCenter();
		float d = sqrt(pow(p.x - p0.x, 2) + pow(p.y - p0.y, 2));
		return d - radius;
	}

	float getGravityAtHeight(float height)
	{
		return -9.81f;
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

	float getRadius() {
		return radius;
	}

	float getAltitudeDensity(const float altitude)
	{
		float temperature = getAltitudeTemperature(altitude);
		float pressure = getAltitudePressure(altitude);
		return pressure * 100.0f/ (temperature + 273.15f) * specificGassConstant;
	}

private:
	float radius;
	sf::CircleShape shape;
	
	float specificGassConstant = 287.058f;
	float sealevelAirPressure = 1012.5f;
	float seaLevelAirTemperature = 20.0f;
	float temperatureLapseRate = 0.00649f;
	float tropopauseAltitude = 11000.0f;

	float getAltitudePressure(const float altitude)
	{
		//auto e = std::pow((1.0f - (0.0000225577f * 10)), 5.25588f);
		return std::max(sealevelAirPressure * exp(-altitude/1000.0f), 0.0f);
	}

	float getAltitudeTemperature(const float altitude)
	{
		return seaLevelAirTemperature - (temperatureLapseRate * std::min(1000.0f, tropopauseAltitude));
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(shape, states);
	}
};