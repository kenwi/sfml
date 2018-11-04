#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Grid.hpp"
#include "FramerateComponent.hpp"

class GWorld : public sf::Drawable, public sf::Transformable
{
public:
	GWorld(sf::RenderWindow &renderWindow)
		: ground(0)
		, cameraLocalPosition(0.0f, 0.0f)
		, window(&renderWindow)
	{
		int numCells = 20;
		auto view = window->getDefaultView();

		Grid *grid = new Grid(view.getSize().x, view.getSize().y, view.getSize().x/numCells);
		pGrid = grid;
		drawables.push_back(grid);

		Earth *earth = new Earth(100.0f, view.getCenter());
		drawables.push_back(earth);

		GFramerateComponent *testComponent = new GFramerateComponent();
		components.push_back(testComponent);
	}

	~GWorld()
	{
		std::cout << "World cleanup" << std::endl;
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

	vector<GameComponent*> getComponentQueue()
	{
		return components;
	}

private:
	float ground;
	sf::Vector2f cameraLocalPosition;
	Grid *pGrid;
	vector<sf::Drawable*> drawables;
	vector<GameComponent*> components;
	sf::RenderWindow *window;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = NULL;
		//target.draw(shape, states);
	}
};