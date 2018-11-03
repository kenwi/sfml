#pragma once

#include "SecondDerivativeBase.hpp"

class RKN // Runge-kutta-nystrøm
{
public:
	RKN(SecondDerivativeBase *derivative)
		: derivative(derivative)
	{
		h = t0 = y0 = d0 = dy0 = d2y0 = 0;
	}

	int Step(double &t1, double &y1, double &dy1, double &d2y1)
	{
		double h2 = h * h;
		double k1 = d2y0;
		double k2 = derivative->getValue(t0 + h / 2, y0 + h / 2 * dy0 + h2 / 8 * k1, dy0 + h / 2 * k1);
		double k3 = derivative->getValue(t0 + h / 2, y0 + h / 2 * dy0 + h2 / 8 * k2, dy0 + h / 2 * k2);
		double k4 = derivative->getValue(t0 + h, y0 + h * dy0 * h2 / 2 * k3, dy0 + h * k3);

		t1 = t0 + h;
		y1 = y0 + h * dy0 + h2 / 6 * (k1 + k2 + k3);
		dy1 = dy0 + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
		d2y1 = derivative->getValue(t1, y1, dy1);

		t0 = t1;
		y0 = y1;
		dy0 = dy1;
		d2y0 = d2y1;
		return 0;
	}

private:
	SecondDerivativeBase *derivative;
	double h;
	double t0;
	double y0;
	double d0;
	double dy0;
	double d2y0;
};