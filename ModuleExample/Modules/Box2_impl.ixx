#if 1
//export module box2:impl;

//export int helper_calc(int w, int h);
#else
module box2:impl;  // implementation partition

// implementation of Box2 template
template<typename T> Box2<T>::Box2(const T& value) : m_value(value) {}
template<typename T> T Box2<T>::get() const { return m_value; }
template<typename T> void Box2<T>::set(const T& value) { m_value = value; }

// implementation of simple function using Box2
int add_one(int x) { return x + 1; }
#endif

