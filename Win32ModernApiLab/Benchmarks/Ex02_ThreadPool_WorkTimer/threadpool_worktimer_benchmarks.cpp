#include <benchmark/benchmark.h>
#include <vector>
#include <memory>
#include "classicthreadpipeline.h"
#include "modernthreadpoolpipeline.h"
#include "threadpool_worktimer_benchmarks.h"

#if 1
BENCHMARK_TEMPLATE(BM_Pipeline_Single, ClassicThreadPipeline)->Range(10000, 100000)->UseRealTime();
BENCHMARK_TEMPLATE(BM_Pipeline_Single, ModernThreadPoolPipeline)->Range(10000, 100000)->UseRealTime();
#endif

#if 1
BENCHMARK_TEMPLATE(BM_Pipeline_Multi, ClassicThreadPipeline)->Range(10000, 100000)->Threads(2)->Threads(4)->Threads(8)->Threads(16)->UseRealTime();
BENCHMARK_TEMPLATE(BM_Pipeline_Multi, ModernThreadPoolPipeline)->Range(10000, 100000)->Threads(2)->Threads(4)->Threads(8)->Threads(16)->UseRealTime();
#endif
