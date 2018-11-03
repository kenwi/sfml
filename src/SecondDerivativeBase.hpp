#pragma once

class SecondDerivativeBase
{
public:
	virtual float getValue(double x, double y, double dy) = 0;
};