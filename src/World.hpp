#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Grid.hpp"

class GWorld : public sf::Drawable, public sf::Transformable
{
public:
	GWorld()
		: ground(0)
		, cameraLocalPosition(0.0f, 0.0f)
	{
		Grid *grid = new Grid(100, 100, 10);
		pGrid = grid;
		drawables.push_back(grid);
	}

	void update(float deltaTime)
	{

	}

	void draw()
	{
		
	}
	
	vector<sf::Drawable*> getDrawQueue()
	{
		return drawables;
	}

private:
	float ground;
	sf::Vector2f cameraLocalPosition;
	Grid *pGrid;
	vector<sf::Drawable*> drawables;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		//target.draw(shape, states);
	}
};