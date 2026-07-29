#if 1
import box2;
#include <iostream>

int main()
{
	Box2 b(3, 4);
	std::cout << b.area() << "\n";
}

#else

import box2;
import <iostream>;
import <string>;

int main()
{
	Box2<int> b1(10);
	std::cout << "b1.get() = " << b1.get() << "\n";
	b1.set(20);
	std::cout << "b1.get() = " << b1.get() << "\n";

	Box2<std::string> b2("Hello");
	std::cout << "b2.get() = " << b2.get() << "\n";
	b2.set("World");
	std::cout << "b2.get() = " << b2.get() << "\n";

	std::cout << "add_one(5) = " << add_one(5) << "\n";
	return 0;
}
#endif
