#pragma once

#include <iostream>

#include "ComponentBase.hpp"

class GFramerateComponent : public GameComponent
{
	float time;
	float totalTime;
	int totalFrames;

public:
	GFramerateComponent()
		: time(0.0f)
		, totalTime(0.0f)
		, totalFrames(0)
	{
		std::cout.precision(5);
		std::cout.setf(ios::fixed);
		std::cout << "Set precision" << std::endl;
	}

	void update(float deltaTime)
	{
		time += deltaTime;
		totalTime += deltaTime;
		totalFrames++;

		if (totalFrames % 2000)
			return;

		float aps = totalFrames / time;
		std::cout << "aps: " << aps << ", totalTime: " << totalTime << ", deltaTime: " << deltaTime << std::endl;
		time = 0.0f;
		totalFrames = 0;
	}
};
