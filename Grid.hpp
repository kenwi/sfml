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
        Grid(int width, int height, int size)
            : Width(width)
            , Height(height)
            , Size(size)
        {
            Columns = width / Size;
            Rows =  height / Size;

            createVertices(vertices);
        }

        Grid(int width, int height, sf::Vector2i size)
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
                    int x = std::clamp(i * Size, 0, Width);
                    int y = std::clamp(j * Size, 0, Height);

                    sf::Vertex vertex = sf::Vertex(sf::Vector2f(x, y));

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