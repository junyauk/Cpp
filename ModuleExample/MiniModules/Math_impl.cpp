module math;

namespace math
{

	double square(double x)
	{
		return x * x;
	}
	double hypotenuse(double a, double b)
	{
		return std::sqrt(square(a) + square(b));
	}
}