#if 1
import box2;

Box2::Box2(int w, int h) : w(w), h(h) {}

int Box2::area() const {
    return w * h;
}
#else
module box2;

import <string>;

import box2;

template class Box2<int>;
template class Box2<double>;
template class Box2<std::string>;
#endif
