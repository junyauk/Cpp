#include "pch.h"
#include "..\02_CoroutineGenerator\NumberGenerator.h"
#include <ranges>

using namespace CoroutineGenerator;

namespace CoroutineGenerator_Test
{
	class CoroutineGeneratorTest : public ::testing::Test {};

    // ------------------------------------------------------------------------
    TEST_F(CoroutineGeneratorTest, A_PrimeGenerationTest)
    {
        NumberGenerator gen;
        std::vector<int> primes;

        // Run Generator
        for (const auto& p : gen.generate_primes_up_to(10))
        {
            primes.push_back(p);
        }

        // Verify (2, 3, 5, 7)
        std::vector<int> expected_primes = { 2, 3, 5, 7 };

        std::cout << "--- Generator Test (A. generate primes) ---" << std::endl;
        std::cout << "  Generated Primes Count: " << primes.size() << std::endl;

        EXPECT_EQ(primes, expected_primes);
    }

    // ------------------------------------------------------------------------
    TEST_F(CoroutineGeneratorTest, B_HistoryStatePreservationTest)
    {
        NumberGenerator gen;
        std::vector<int> first_part;
        std::vector<int> second_part;

        // 1. Run generator
        Generator<int> non_primes_gen = gen.generate_closest_non_primes<int>(10);

        // Get iterators
        auto it = non_primes_gen.begin();
        auto end = non_primes_gen.end();

        // 2. Get the first 2 elements
        // Expected: 1, 4

        // Failsafe: 
        if (it != end) {
            first_part.push_back(*it); // Get 1
            ++it;
        }
        if (it != end) {
            first_part.push_back(*it); // Get 44
            ++it;
        }

        // 3. Get rest
        // Expected: 6, 8, 9, 10
        // for until end
        for (; it != end; ++it)
        {
            second_part.push_back(*it);
        }

        // 4. Verify

        // First expected values: 1, 4
        std::vector<int> expected_first = { 1, 4 };
        // Rest expected values: 6, 8, 9, 10
        std::vector<int> expected_second = { 6, 8, 9, 10 };

        std::cout << "\n--- Generator Test (B. State Persistence Test - Complete) ---" << std::endl;

        // Verify A: first part
        EXPECT_EQ(first_part, expected_first) << "The retrieval of the first two non-prime numbers failed.";

        // Verify B: rest part
        EXPECT_EQ(second_part, expected_second) << "Failed to maintain the generator's state and retrieve the remaining elements.";
    }
    // ------------------------------------------------------------------------
    TEST_F(CoroutineGeneratorTest, C_CompositeSequenceTest)
    {
        NumberGenerator gen;

        // 1. Run Generator
        // Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, (144 - stop)
        auto fib_generator = gen.generate_fibonacci(100);
        std::vector<long long> fib_values;
        std::copy(fib_generator.begin(), fib_generator.end(), std::back_inserter(fib_values));

        // 2. Ranges processing pipeline
        long long sum_of_even_fibs = 0;

        // Verify that Generator iterators are compatible with standard Ranges
        // * std::views::filter: Filtering even
        // * std::accumulate: sum total
        
        // Filtering even fibs using Ranges view 
        auto is_even = [](long long n) { return n % 2 == 0; };
        auto even_fibs_view = std::views::filter(fib_values, is_even);

        // Ranges view provides begin/end iterators, enabling integration with STL algorithms.
        sum_of_even_fibs = std::accumulate(even_fibs_view.begin(), even_fibs_view.end(), 0LL);

        // Expected Even Fibonacci numbers up to 100: 0, 2, 8, 34
        // Expected Sum: 0 + 2 + 8 + 34 = 44

        long long expected_sum = 44;

        std::cout << "\n--- Generator Test (C. Composite Sequences - Ranges Integration) ---" << std::endl;
        std::cout << "  Calculated Sum of Even Fibs (up to 100): " << sum_of_even_fibs << std::endl;

        EXPECT_EQ(sum_of_even_fibs, expected_sum);
    }

    // ------------------------------------------------------------------------
    TEST_F(CoroutineGeneratorTest, D_AlternatingGenerationTest)
    {
        NumberGenerator gen;
        std::vector<int> results;

        // 1. Preparing generator
        // Fibonacci (up to 20): 0, 1, 1, 2, 3, 5, 8, 13
        Generator<int> fib_gen = gen.generate_fibonacci(20);

        // Primes (up to 15): 2, 3, 5, 7, 11, 13
        Generator<int> prime_gen = gen.generate_primes_up_to(15);

        // 2. Combine generator
        // Sequence should be: 
        // A: 0, B: 2, A: 1, B: 3, A: 1, B: 5, A: 2, B: 7, 
        // A: 3, B: 11, A: 5, B: 13, A: 8, (A ends: 13), (B ends: 13)

        // Expected: 0, 2, 1, 3, 1, 5, 2, 7, 3, 11, 5, 13, 8, 13
        for (const auto& n : gen.generate_alternating(std::move(fib_gen), std::move(prime_gen)))
        {
            results.push_back(n);
        }

        // 3. Verify
        std::vector<int> expected_results = { 0, 2, 1, 3, 1, 5, 2, 7, 3, 11, 5, 13, 8, 13 };

        std::cout << "\n--- Generator Test (D. Combined Operation of Multiple Generators) ---" << std::endl;
        std::cout << "  Generated Alternating Count: " << results.size() << std::endl;

        EXPECT_EQ(results, expected_results);

    }

    // ------------------------------------------------------------------------
    TEST_F(CoroutineGeneratorTest, E_ConditionalYieldFilterTest)
    {
        NumberGenerator gen;
        std::vector<int> results;

        // 1. Run generator (Generate even numbers up to 10)
        // Expected: 0, 2, 4, 6, 8, 10
        for (const auto& n : gen.generate_even_numbers_up_to<int>(10))
        {
            results.push_back(n);
        }

        // 2. Verify
        std::vector<int> expected = { 0, 2, 4, 6, 8, 10 };

        std::cout << "\n--- Generator Test (F. conditioned Yield) ---" << std::endl;
        EXPECT_EQ(results, expected) << "Even number filtered generator failed.";
    }
}

