#if 1
export module box2;

export struct Box2 {
    int w{};
    int h{};
    Box2(int w, int h);
    int area() const;
};

#else
export module box2;

// Declare Box2 template
export template<typename T>
class Box2
{
private:
    T m_value;
public:
    Box2(const T& value);
    T get() const;
    void set(const T& value);
};

// Simple function using Box2
export int add_one(int x);

import :impl; // import the implementation partition
#endif
