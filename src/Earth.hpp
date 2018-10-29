#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

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

		/*sf::Image buffer = createAtmosphere(windowWidth, windowHeight, earth);
		sf::Texture texture;
		texture.loadFromImage(buffer);
		sf::Sprite atmosphere;
		atmosphere.setTexture(texture);
		*/
		setCenterAt(initialPosition.x, initialPosition.y);
	}

	sf::Image createAtmosphere(int windowWidth, int windowHeight, int zoomLevel)
	{
		return createAtmosphere(windowWidth, windowHeight, zoomLevel, (*this));
	}

	sf::Image createAtmosphere(int windowWidth, int windowHeight, int zoomLevel, Earth& earth)
	{
		sf::Image buffer;
		buffer.create(windowWidth, windowHeight);

		for (int x = 0; x < buffer.getSize().x; x++) {
			for (size_t y = 0; y < buffer.getSize().y; y++)
			{
				sf::Vector2f p(x * zoomLevel, y * zoomLevel);
				sf::Vector2f p0(earth.getCenter().x *zoomLevel, earth.getCenter().y * zoomLevel);
				float altitude = (float)sqrt(pow(p.x - p0.x, 2.0f) + pow(p.y - p0.y, 2.0f)) - earth.getRadius();
				altitude *= 100;

				float density = earth.getAltitudeDensity(altitude);
				float alpha = clamp<float>(density, 0.0f, 1.0f);

				sf::Color blue(sf::Color::Blue);
				sf::Color black(sf::Color::Black);

				float r = blue.r * alpha + (black.r * (1.0f - alpha));
				float g = blue.g * alpha + (black.g * (1.0f - alpha));
				float b = blue.b * alpha + (black.b * (1.0f - alpha));

				buffer.setPixel(x, y, sf::Color(r, g, b));
			}
		}
		return buffer;
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

	float CalculateDrag(float velocity, float altitude, float radius)
	{
		float density = getAltitudeDensity(altitude) / pow(1000, 3);

		float crossSection = 3.141592f * (radius * radius);
		float Cd = 0.5f;
		// drag = d = dragcoefficient * 0.5 * density * velocity^2 * reference area 
		// coefficient of sphere = 0.5
		return Cd * 0.5 * density * (velocity * velocity) * crossSection;
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

	float getRadius() 
	{
		return radius;
	}

	float getAltitudeDensity(const float altitude)
	{
		float temperature = getAltitudeTemperature(altitude);
		float pressure = getAltitudePressure(altitude);
		return pressure / (temperature + 273.15f) * specificGassConstant;
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