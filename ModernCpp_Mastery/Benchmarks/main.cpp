#include <benchmark/benchmark.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    // 1. If no command-line filter was supplied, show an interactive prompt
    if (argc == 1)
    {
        std::cout << "Select Exercise Benchmark to Run:\n";
        std::cout << "1. Ex01_ImagePipeline\n";
        std::cout << "2. Ex02_JobSystem\n";
        std::cout << "3. Ex03_OrderBookProcessor\n";
        std::cout << "4. Run All\n";
        std::cout << "Enter choice (1-4): ";

        int choice = 0;
        std::cin >> choice;

        switch (choice)
        {
        case 1: ::benchmark::SetBenchmarkFilter("Ex01"); break;
        case 2: ::benchmark::SetBenchmarkFilter("Ex02"); break;
        case 3: ::benchmark::SetBenchmarkFilter("Ex03"); break;
        default: break; // Runs everything
        }
    }

    // 2. Initialize and execute
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return 0;
}
