#pragma once
#include <concepts>
#include <string>
#include <vector>

namespace Concepts_Basic
{
    /**
     * @brief A custom concept that requires a type T to support
     * the less-than operator (<) and the greater-than operator (>)
     * with itself.
     * @tparam T The type to check.
     */
    template<typename T>
    concept CompareLessGreater = requires(T a, T b)
    {
        // Requires that the less-than operation is valid and returns a bool-convertible type.
        { a < b } -> std::convertible_to<bool>;
        // Requires that the greater-than operation is valid and returns a bool-convertible type.
        { a > b } -> std::convertible_to<bool>;
    };

    /**
     * @brief Utility class to demonstrate C++20 Concepts for template constraints.
     */
    class ConceptsBasic
    {
    public:
        ConceptsBasic() = default;

        /**
         * @brief Checks if the first parameter is greater than the second parameter.
         * This function is constrained by the custom CompareLessGreater concept.
         * * @tparam T The type of the parameters, must satisfy CompareLessGreater.
         * @param m_a The first value.
         * @param m_b The second value.
         * @return true if m_a > m_b, false otherwise.
         */
        template<CompareLessGreater T>
        bool isGreaterThan(const T& m_a, const T& m_b) const
        {
            return m_a > m_b;
        }

        /**
         * @brief Checks if the two parameters are equal.
         * This function is constrained by the standard C++ concept std::equality_comparable.
         * * @tparam T The type of the parameters, must satisfy std::equality_comparable.
         * @param m_a The first value.
         * @param m_b The second value.
         * @return true if m_a == m_b, false otherwise.
         */
        template<std::equality_comparable T>
        bool areEqual(const T& m_a, const T& m_b) const
        {
            return m_a == m_b;
        }

        /**
         * @brief Checks if a container is empty.
         * Uses a concise function template syntax where 'auto' is constrained by a concept.
         * * @tparam T The container type, must satisfy std::ranges::range and have an 'empty' method.
         * @param m_container The container object.
         * @return true if the container is empty, false otherwise.
         */
        template<typename T>
        bool isContainerEmpty(const T& m_container) const
            requires requires
                        {
                            m_container.empty();
                        }
        {
            return m_container.empty();
        }

        // --- Overload resolution demonstration using Concepts ---

        /**
         * @brief Specialization for any integral type.
         * * @tparam T Must be a standard integral type.
         */
        template <std::integral T>
        std::string getTypeInfo(const T&) const
        {
            return "Integral Type";
        }

        /**
         * @brief Specialization for any floating point type.
         * This function is preferred over the unconstrained version if the type is floating_point.
         * * @tparam T Must be a standard floating point type.
         */
        template<std::floating_point T>
        std::string getTypeInfo(const T&) const
        {
            return "Floating Point Type";
        }

        /**
         * @brief General unconstrained version (catch-all).
         * This is only selected if the type does not satisfy any other constrained template.
         * * @tparam T Any type.
         */
        template<typename T>
        std::string getTypeInfo(const T&) const
        {
            return "Other Type";
        }
    };
}

