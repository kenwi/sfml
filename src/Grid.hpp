#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <cmath>
#include <algorithm>


class Grid : public sf::Drawable, public sf::Transformable
{
    private:        
        int Size;
        int Height;
        int Width;

        int Columns;
        int Rows;

        sf::VertexArray vertices;
    public:
        Grid(const int width, const int height, const int size)
            : Width(width)
            , Height(height)
            , Size(size)
        {
            Columns = width / Size;
            Rows =  height / Size;

            createVertices(vertices);
        }

        Grid(const int width, const int height, const sf::Vector2i size)
            : Width(width)
            , Height(height)
        {
            Columns = width / size.x;
            Rows = height  / size.y;

            createVertices(vertices);
        }

    private:
        void createVertices(sf::VertexArray& vertices)
        {
            vertices.setPrimitiveType(sf::Points);

            for(int i=0; i<Columns; i++)
            {
                for(int j=0; j<Rows; j++)
                {                    
                    const float x = (float)std::clamp(i * Size, 0, Width);
                    const float y = (float)std::clamp(j * Size, 0, Height);

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
};