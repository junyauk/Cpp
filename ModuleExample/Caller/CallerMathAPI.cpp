#include "pch.h"
#include "CallerMathAPI.h"

import math;

namespace Caller
{
	double computeSquare(double x)
	{
		return math::square(x);
	}

	double computeHypotenuse(double a, double b)
	{
		return math::hypotenuse(a, b);
	}
}

