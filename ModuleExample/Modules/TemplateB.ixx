export module templateb;

import templatea;

export
template<typename T>
T add_then_mul(T a, T b, T c)
{
	return mul(add(a, b), c);
}
