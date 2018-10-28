#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <cmath>
#include <algorithm>

class Grid : public sf::Drawable, public sf::Transformable
{
public:
	Grid(const int width, const int height, const int size)
		: width(width)
		, height(height)
		, size(size)
	{
		columns = width / size;
		rows = height / size;

		createVertices(vertices);
	}

	Grid(const int width, const int height, const sf::Vector2i size)
		: width(width)
		, height(height)
	{
		columns = width / size.x;
		rows = height / size.y;

		createVertices(vertices);
	}

private:
	void createVertices(std::vector<sf::Vertex>& vertices)
	{
		for (int x = 0; x < columns+1; x++)
		{
			vertices.push_back(sf::Vertex(sf::Vector2f(x * size, 0.0f)));
      			vertices.push_back(sf::Vertex(sf::Vector2f(x * size, height)));
		}
		
		for (int y = 0; y < rows+1; y++)
		{
			vertices.push_back(sf::Vertex(sf::Vector2f(0, y * size)));
			vertices.push_back(sf::Vertex(sf::Vector2f(width, y * size)));
		}
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;		
		
		target.draw(&vertices[0], vertices.size(), sf::Lines);
	}

	int size;
	int height;
	int width;

	int columns;
	int rows;
	
	std::vector<sf::Vertex> vertices;
};