#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <utility>
#include <string>

namespace LambdaImprovements
{
	template<typename T, typename... Args>
	std::function<std::unique_ptr<T>()> makeFactory(Args&&... args)
	{
		// parameters are copied and packed as tuple
		return [tuple = std::make_tuple(std::forward<Args>(args)...), used = false]() mutable
			{
				if (used) // This flag allow the function runce once
				{
					throw std::runtime_error("Factory already used");
				}
				used = true;
				// The tuple contains parameters is passed as the "unpackedArgs" parameter
				// The std::apply will unpack the tuple

				// The std::function created by makeFactory() will create T (Widgetin this sample) and set values stored in the tuple.
				return std::apply([](auto&&... unpackedArgs)
					{
						return std::make_unique<T>(std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
					}, std::move(tuple)); // This tuple will be moved, after that, the contents in the tuple is unknown (not reliable)
			};
	}

	struct Widget
	{
		std::string name;
		int value;

		Widget(std::string n, int v) : name(n), value(v) { std::cout << "Widget(" << name << ", " << value << ") constructed\n"; }
		~Widget() { std::cout << "Widget(" << name << ") destroyed\n"; }
	};

	void RunFactoryExample()
	{
		auto factory = makeFactory<Widget>("Engine", 42); // "Engine" and "42" are moved as tuple
		std::unique_ptr<Widget> w1 = factory();
		std::cout << "Created: " << w1->name << ", " << w1->value << std::endl;

		try
		{
			std::unique_ptr<Widget> w2 = factory();
			std::cout << "Created: " << w2->name << ", " << w2->value << std::endl;
		}
		catch (...)
		{
			std::cout << "Factory can't be reused safely.\n";
		}
	}
}
