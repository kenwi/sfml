#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Grid.hpp"
#include "FramerateComponent.hpp"

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

		GFramerateComponent *testComponent = new GFramerateComponent();
		components.push_back(testComponent);
	}

	~GWorld()
	{
		for (auto c : components)
			delete c;

		for (auto d : drawables)
			delete d;
	}

	void update(float deltaTime)
	{
		for (auto c : components)
			c->update(deltaTime);
	}

	vector<sf::Drawable*> getDrawQueue()
	{
		return drawables;
	}

	vector<GComponent*> getComponentQueue()
	{
		return components;
	}

private:
	float ground;
	sf::Vector2f cameraLocalPosition;
	Grid *pGrid;
	vector<sf::Drawable*> drawables;
	vector<GComponent*> components;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		//target.draw(shape, states);
	}
};