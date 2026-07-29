export module templatea;

template<typename T>
T add(T a, T b)
{
	return a + b;
}

template<typename T>
T mul(T a, T b)
{
	return a * b;
}

template int add(int a, int b);
template int mul(int a, int b);
template double mul(double a, double b);
