#pragma once
#include <coroutine>
#include <iostream>
#include <string>
#include <optional>
#include <utility>

namespace Coroutines_Basic
{
    // --- Boilerplate Code for Generator Implementation ---

    // 1. Forward declaration of the Generator struct
    template<typename T>
    struct Generator;

    // 2. The promise type holds the state and controls the coroutine execution
    template<typename T>
    struct GeneratorPromise
    {
        T m_value;

        // 2-1. Returns the handle used to control the coroutine
        Generator<T> get_return_object()
        {
            return Generator<T>{std::coroutine_handle<GeneratorPromise<T>>::from_promise(*this)};
        }

        // 2-2. Suspends execution before the coroutine body runs (Lazy execution)
        std::suspend_always initial_suspend() { return {}; }
        // 2-3. Suspends execution after the coroutine body runs to completion (co_return)
        std::suspend_always final_suspend() noexcept { return {}; }
        // 2-4. Executed when co_yield is called
        std::suspend_always yield_value(T value)
        {
            m_value = std::move(value);
            return {};  // Suspends and returns the yielded value
        }

        // 2-5. Executed when co_return is called
        void return_void() {}

        // 2-6. Exception handling
        void unhandled_exception() { throw; }
    };

    // 3. The wrapper struct that holds the coroutine handle and provides the interface
    template<typename T>
    struct Generator
    {
        using promise_type = GeneratorPromise<T>;
        std::coroutine_handle<promise_type> m_handle;

        // Constructor
        Generator(std::coroutine_handle<promise_type> h) : m_handle(h){}

        // Destructor: Destroys the handle and frees allocated memory
        ~Generator()
        {
            if (m_handle)
            {
                m_handle.destroy();
            }
        }

        // Rule of Five: Only move operations are allowed for handles
        Generator(const Generator& other) = delete;
        Generator(Generator&& other) noexcept : m_handle(other.m_handle)
        {
            other.m_handle = nullptr;
        }

        // Method to resume the coroutine and get the next value
        std::optional<T> next()
        {
            if (m_handle.done())
            {
                return std::nullopt;    // Coroutine is finished
            }
            m_handle.resume();  // Resumes execution until the next co_yield or co_return
            if (m_handle.done())
            {
                return std::nullopt;    // Coroutine finished after resuming
            }
            return m_handle.promise().m_value;    // Return the value yielded
        }
    };

    // --- Coroutines_Basic Class ---
    class CoroutinesBasic
    {
    public:
        CoroutinesBasic() = default;

        /**
         * @brief A coroutine that uses co_yield to sequentially generate a sequence of values.
         * @param start The starting value.
         * @param count The number of elements to generate.
         * @return A Generator<int> object that can produce values one by one.
         */
        Generator<int> createSequenceGenerator(int start, int count) const
        {
            for (auto i = 0; i < count; ++i)
            {
                // co_yield: returns a value and suspends execution.
                co_yield start + i;
            }
            // co_return: terminates the coroutine.
            co_return;
        }
    };

    // ------------------------------------------------------------------------

    /**
     * @brief Demonstrates the use of co_yield for generating sequences like Fibonacci.
     * This example highlights state preservation and lazy evaluation.
     */
    class CoroutinesGenerator
    {
    public:
        CoroutinesGenerator() = default;

        /**
         * @brief A coroutine that generates the Fibonacci sequence up to a given limit.
         * The state (a and b) is preserved across each co_yield suspension.
         * @param limit The maximum value to generate (exclusive).
         * @return A Generator<int> object for the sequence.
         */
        Generator<int> createFibonacciGenerator(int limit) const
        {
            // Initial state variables (preserved across suspensions)
            int a = 0;
            int b = 1;

            if (limit <= 0)
            {
                co_return;
            }

            co_yield a; // First element: 0

            if (limit > 1)
            {
                co_yield b; // Second element: 1
            }

            while (true)
            {
                int next = a + b;
                if (next >= limit)
                {
                    co_return;
                }
                // co_yield suspends execution, preserving the values of a and b.
                co_yield next;

                // Execution resumes here on the next() call, updating the state.
                a = b;
                b = next;
            }
        }

        /**
         * @brief A coroutine that generates an infinite sequence of increasing integers.
         * The sequence is halted externally by the consumer's loop condition.
         * This demonstrates state preservation and infinite stream potential.
         * @param start The starting value.
         * @return A Generator<int> object for the infinite sequence.
         */
        Generator<int> createInfiniteNumberGenerator(int start) const
        {
            int current = start;
            // Loop indefinitely; co_yield will preserve 'current' between suspensions.
            while (true)
            {
                co_yield current;
                current++;
            }
            // co_return is unreachable, showing the stream is theoretically infinite.
        }
    };
}
