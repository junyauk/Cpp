#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <cmath>
#include <execution>

namespace ParallelSTL_Advance
{
    // --- 1. Definition of Bottleneck Processing ---
    // Simulates a CPU-intensive, complex calculation for each element.
    double complexCalculation(double x)
    {
        // Simple but CPU-intensive operation: sqrt(sin^2 + cos^2) after many iterations
        double result = x;
        for (auto i = 0; i < 1000; ++i)
        {
            result = std::sqrt(std::sin(result) * std::sin(result) + std::cos(result) * std::cos(result));
        }
        return result + x;
    }

    class ParallelSTL_Advance
    {
    private:
        std::vector<double> m_data;
    public:
        ParallelSTL_Advance(size_t size)
        {
            m_data.resize(size);
            std::iota(m_data.begin(), m_data.end(), 1.0);
        }

        // --- 1. Application: Parallel Transformation (High Compute Load) ---
        // Measures time taken for a complex transform using different execution policies.
        long long benchmarkTransform(std::execution::sequenced_policy policy)
        {
            std::vector<double> result(m_data.size());
            auto start = std::chrono::high_resolution_clock::now();

            // Apply complexCalculation to all elements in parallel
            std::transform(policy, m_data.begin(), m_data.end(), result.begin(), complexCalculation);

            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        long long benchmarkTransform(std::execution::parallel_unsequenced_policy policy)
        {
            std::vector<double> result(m_data.size());
            auto start = std::chrono::high_resolution_clock::now();

            // Apply complexCalculation to all elements in parallel
            std::transform(policy, m_data.begin(), m_data.end(), result.begin(), complexCalculation);

            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        long long benchmarkTransform(std::execution::parallel_policy policy)
        {
            std::vector<double> result(m_data.size());
            auto start = std::chrono::high_resolution_clock::now();

            // Apply complexCalculation to all elements in parallel
            std::transform(policy, m_data.begin(), m_data.end(), result.begin(), complexCalculation);

            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        // --- 2. Application: Execution Policy Comparison (std::for_each) ---
        // Measures sequential vs. parallel for_each (useful for I/O bound tasks/side effects)
        long long benchmarkForEach(std::execution::sequenced_policy policy)
        {
            auto start = std::chrono::high_resolution_clock::now();
            // Sequential policy
            std::for_each(policy, m_data.begin(), m_data.end(),
                [](double& val) 
                {
                    val += 1.0; 
                });
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        long long benchmarkForEach(std::execution::parallel_policy policy)
        {
            auto start = std::chrono::high_resolution_clock::now();
            // Parallel policy
            std::for_each(policy, m_data.begin(), m_data.end(),
                [](double& val)
                {
                    val += 1.0;
                });
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        // Helper to check calculation consistency (ensures parallel result is correct)
        double checkSum() const
        {
            return std::accumulate(m_data.begin(), m_data.end(), 0.0);
        }


    };

}

