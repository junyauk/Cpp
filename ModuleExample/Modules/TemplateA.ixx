export module templatea;

export
template<typename T>
T add(T a, T b);

export
template<typename T>
T mul(T a, T b);

extern template int add(int a, int b);
extern template int mul(int a, int b);
extern template double mul(double a, double b);
