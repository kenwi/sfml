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
	void createVertices(sf::VertexArray& vertices)
	{
		vertices.setPrimitiveType(sf::Points);

		for (int i = 0; i < columns; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				const float x = (float)std::clamp(i * size, 0, width);
				const float y = (float)std::clamp(j * size, 0, height);

				const sf::Vector2f v(x, y);
				const sf::Vertex vertex = sf::Vertex(v);

				vertices.append(vertex);
			}
		}
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;

		target.draw(vertices, states);
	}

	int size;
	int height;
	int width;

	int columns;
	int rows;

	sf::VertexArray vertices;
};