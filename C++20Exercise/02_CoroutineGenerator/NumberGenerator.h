#pragma once
#include <iostream>
#include <coroutine>
#include <vector>
#include <numeric>
#include <ranges>
#include <concepts>
#include <cmath> // std::sqrt
#include "Generator.h"

namespace CoroutineGenerator
{
	// Concepts
	template<typename T>
	concept IntegralArgument = std::integral<T>;

	class NumberGenerator
	{
	private:
		// Simple Prime Number Checker Helper (Utilizing STL/Concepts Learning Content)
		template<IntegralArgument T>
		bool is_prime(T n) const
		{
			// T is an IntegralArgument, the calculation is guaranteed to be safe.
			T limit = static_cast<T>(std::sqrt(n));
			for (T i = 2; i <= limit; ++i)
			{
				if (n % i == 0)
				{
					return false;
				}
			}
			return true;
		}
	public:
		// Exercise A: Prime Number Generation (Most Basic Use of co_yield)
		Generator<int> generate_primes_up_to(IntegralArgument auto max_value)
		{
			for (int i = 2; i <= max_value; ++i)
			{
				if (is_prime(i))
				{
					co_yield i;	// Suspend execution and maintain state until the next request
				}
			}
		}

		// --------------------------------------------------------------------------
		/**
		 * @brief Generates numbers that are NOT prime and are greater than the previously found prime.
		 * @note This demonstrates how co_yield preserves local state (last_prime_value).
		 * @param max_value The maximum number to check.
		 * @return A Generator sequence of non-prime numbers that follow a prime.
		 */
		template<typename T>
		Generator<T> generate_closest_non_primes(T max_value)
		{
			if (max_value >= 1)
			{
				co_yield (T)1;
			}

			// 2. Iterate through potential numbers
			for (T i = 2; i <= max_value; ++i)
			{
				if (is_prime(i))
				{
					continue;
				}
				co_yield i;
			}
		}	// generate_closest_non_prime()

		// --------------------------------------------------------------------------

		/**
		 * @brief Generates the Fibonacci sequence up to a maximum value.
		 * @note This is a classic demonstration of co_yield state preservation.
		 * @param max_value The maximum value of the Fibonacci number to yield.
		 * @return A Generator sequence of Fibonacci numbers.
		 */
		template<typename T>
		Generator<T> generate_fibonacci(T max_value)
		{
			// 1. local state (previous two numbers) preserved by coroutine
			long long a = 0;	// F0
			long long b = 1;	// F1

			if (a <= max_value)
			{
				co_yield static_cast<T>(a);
			}

			// Generate subsequent numbers
			while (b<=max_value)
			{
				// First, yield the current b
				co_yield static_cast<T>(b);

				long long next = a + b;
				if (next > max_value || next > std::numeric_limits<T>::max())
				{
					break;	// Stop when max_value is executed
				}
				// 3. Update state
				a = b;
				b = next;
			}
		}	// Generate_fibonacchi

		// --------------------------------------------------------------------------
		/**
		 * @brief Generates elements alternating between two different sequences (A and B).
		 * @param genA The first sequence (e.g., Fibonacci).
		 * @param genB The second sequence (e.g., Primes).
		 * @return A Generator sequence yielding elements alternately from A and B.
		 */
		template<typename T>
		Generator<T> generate_alternating(Generator<T> genA, Generator<T> genB)
		{
			// 1. Get generators
			auto itA = genA.begin();
			auto endA = genA.end();

			auto itB = genB.begin();
			auto endB = genB.end();

			// Loop until one of them finished
			while (itA != endA || itB != endB)
			{
				// Get an element from A
				if (itA != endA)
				{
					co_yield *itA;
					++itA;	// Next A
				}

				// Get an element from B
				if (itB != endB)
				{
					co_yield *itB;
					++itB;	// Next B
				}
			}
		}

		// --------------------------------------------------------------------------
		/**
		 * @brief Generate even numbers in the specified range
		 * @tparam T The type of the elements to yield.
		 */		template<typename T>
		Generator<T> generate_even_numbers_up_to(T max_value)
		{
			for (T n = 0; n <= max_value; ++n)
			{
				if (n % 2 == 0)
				{
					co_yield n;
				}
			}
		}
	};
}

