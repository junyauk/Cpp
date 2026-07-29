#pragma once

#include <string>
#include <concepts>
#include <iostream>
#include <type_traits>

// --------------------
// Example01_Simple
// --------------------
template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T>
T add(T a, T b)
{
    return a + b;
}

template int add<int>(int, int);
template double add<double>(double, double);

// --------------------
// Example02_Custom
// --------------------
template <typename T>
concept HasLength = requires(T a)
{
    { a.length() } -> std::convertible_to<std::size_t>;
};

inline void printLength(const HasLength auto& obj)
{
    std::cout << "Length: " << obj.length() << "\n";
}

// --------------------
// Example03_Multiple
// --------------------
template<typename T>
concept SignedValue = (std::integral<T> && std::is_signed_v<T>) || std::floating_point<T>;

template<SignedValue T>
T negativeValue(T value)
{
    return -value;
}

// --------------------
// Example04_Requires
// --------------------
template<typename T>
    requires std::integral<T>
T gcd(T a, T b)
{
    while (b != 0)
    {
        T tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

// --------------------
// Example05_Overload
// --------------------
inline void process(std::integral auto value)
{
    std::cout << "Integral: " << value << "\n";
}

inline void process(std::floating_point auto value)
{
    std::cout << "Floating point: " << value << "\n";
}