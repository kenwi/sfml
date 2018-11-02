#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Game
{
	using namespace sf;

	class Application
	{
	public:
		Application()
			: windowWidth(1024)
			, windowHeight(768)
			, zoomLevel(1)
			, windowCenter(windowWidth * 0.5f, windowHeight * 0.5f)
			, window(VideoMode(windowWidth, windowHeight), "", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize)
			, view(FloatRect(1.0f, 1.0f, 1.0f, 1.0f))
		{

		}

		int Run();

	private:
		int zoomLevel;
		int windowWidth;
		int windowHeight;

		View view;
		Vector2f windowCenter;		
		RenderWindow window;
	};
}