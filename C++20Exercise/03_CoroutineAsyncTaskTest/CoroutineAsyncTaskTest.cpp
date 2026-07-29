#include "pch.h"
#include "..\03_CoroutineAsyncTask\Task.h"

namespace CoroutineAsyncTaskTest
{
    // ------------------------------------------------------------------------
    // Exercise 1: Mastering co_return
    // Task<T> acts as a coroutine function that returns a value via co_return.
    Task<int> calculate_async_sum(int a, int b)
    {
        std::cout << "  [Task] Calculation started...\n";
        // Simulation of an asynchronous operation (time-consuming process)

        int sum = a + b;

        std::cout << "  [Task] Calculation finished. Returning value.\n";
        // co_return stores the task result in promise_type

        co_return sum;
    }


    TEST(CoroutineAsyncTaskTest, A_CoroutineReturnTest)
    {
        // 1. Call the coroutine function
        Task<int> sum_task = calculate_async_sum(15, 27);

        // 2. Execute the Task and retrieve the result (Task.start_and_get_result() calls resume())
        int result = sum_task.start_and_get_result();

        // Verification
        EXPECT_EQ(42, result);

        // 4. Additinal verification: using different parameters
        Task<int> another_task = calculate_async_sum(100, -58);
        EXPECT_EQ(another_task.start_and_get_result(), 42);
    }
#if 1
    // ------------------------------------------------------------------------
    // Exercise 2:
    /**
     * @brief Async Task using co_await to suspend and co_return to finish.
     */
    Task<std::string> async_fetch_data(int id)
    {
        std::cout << "  [Task] Fetching data for ID: " << id << "...\n";

        // Use co_await to suspend execution
        co_await DelayAwaiter{ 500 };

        std::string result = "Data-" + std::to_string(id);
        std::cout << "  [Task] Fetching complete.\n";

        co_return result;
    }

    TEST(CoroutineAsyncTaskTest, B_CoroutineAwaitTest)
    {
        // 1. Initialize Task
        Task<std::string> data_task = async_fetch_data(101);

        std::cout << "  [Main] Created Task 101.\n";

        // 2. Start the task
        // Because of our simple DelayAwaiter, resume() happens during await_suspend
        std::string result = data_task.start_and_get_result();

        // 3. Verification
        EXPECT_EQ(result, "Data-101");
        std::cout << "  [Main] Final Result: " << result << "\n";
    }
#endif

    // ------------------------------------------------------------------------
    // Exercise 3:
    /**
     * @brief Sub-task: Validates the ID.
     */
    Task<bool> validate_id_async(int id)
    {
        std::cout << "    [SubTask] Validating ID: " << id << "...\n";
        co_await DelayAwaiter{ 100 };
        co_return (id > 0);
    }

    /**
     * @brief Main-task: Fetches profile using validate_id_async.
     */
    Task<std::string> fetch_profile_async(int id)
    {
        std::cout << "  [MainTask] Fetching profile for ID: " << id << "\n";
        // Nesting: co_await another Task
        bool is_valid = co_await validate_id_async(id);

        if (!is_valid)
        {
            co_return "Invalid-User";
        }
        co_await DelayAwaiter{ 200 };
        co_return "Profile-of-" + std::to_string(id);
    }

    TEST(CoroutineAsyncTaskTest, C_NestedTaskTest)
    {
        std::cout << "  [Test] Starting Nested Task...\n";

        // 1. Initialize the top-level task
        Task<std::string> main_task = fetch_profile_async(42);

        // 2. Start execution
        std::string result = main_task.start_and_get_result();

        // 3. Verification
        EXPECT_EQ(result, "Profile-of-42");
        std::cout << "  [Test] Main Task Finished. Result: " << result << "\n";
    }

    // ------------------------------------------------------------------------
    // Exercise 4:
    Task<int> error_task_async(int x)
    {
        std::cout << "    [ErrorTask] Starting calculation...\n";
        if (x == 0)
        {
            // Throw exception, out side of co_await
            throw std::runtime_error("Division by zero not allowed.");
        }
        co_await DelayAwaiter{ 50 };
        co_return 100;
    }

    TEST(CoroutineAsyncTaskTest, D_ExceptionHandlingTest)
    {
        Task<int> main_task = error_task_async(0);

        EXPECT_THROW({main_task.start_and_get_result();}, std::runtime_error);

        Task<int> success_task = error_task_async(2);
        EXPECT_EQ(success_task.start_and_get_result(), 100);
    }



}