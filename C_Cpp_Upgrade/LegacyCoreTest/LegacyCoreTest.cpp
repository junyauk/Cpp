#include "pch.h"
#include "..\LegacyCode\LegacyCode.h"

// --- Test Suite 1: Array Sum (Data Structure) ---
TEST(ArraySumTest, BasicSum) {
    int data[] = { 10, 20, 30, 40, 50 };
    size_t count = sizeof(data) / sizeof(data[0]);
    ASSERT_EQ(150L, array_sum_c(data, count));
}

TEST(ArraySumTest, EmptyArray) {
    const int* data = nullptr; // Use nullptr for 0 elements to avoid C2466
    size_t count = 0;
    ASSERT_EQ(0L, array_sum_c(data, count));
}

// --- Test Suite 2: Array Double and Copy (Memory Management) ---
TEST(ArrayDoubleTest, BasicDouble) {
    int data[] = { 1, 5, 10 };
    size_t count = sizeof(data) / sizeof(data[0]);
    int expected[] = { 2, 10, 20 };

    int* result_array = array_double_and_copy(data, count);

    ASSERT_NE(nullptr, result_array);

    for (size_t i = 0; i < count; ++i) {
        ASSERT_EQ(expected[i], result_array[i]);
    }

    // CRITICAL: Caller (test code) must free the memory allocated by malloc
    if (result_array != nullptr) {
        free(result_array);
    }
}

TEST(ArrayDoubleTest, NullInput) {
    int* result_array = array_double_and_copy(nullptr, 10);
    ASSERT_EQ(nullptr, result_array);
}

// --- Test Suite 3: Array Find First (Data Search) ---
TEST(ArraySearchTest, TargetFound) {
    int data[] = { 10, 20, 5, 30, 20, 40 };
    size_t count = sizeof(data) / sizeof(data[0]);

    ASSERT_EQ(1, array_find_first(data, count, 20)); // First occurrence
    ASSERT_EQ(2, array_find_first(data, count, 5));
}

TEST(ArraySearchTest, TargetNotFound) {
    int data[] = { 10, 20, 30 };
    size_t count = sizeof(data) / sizeof(data[0]);

    // Should return count (3) if not found
    ASSERT_EQ(count, array_find_first(data, count, 99));
}

TEST(ArraySearchTest, EmptyArray) {
    const int* data = nullptr;
    size_t count = 0;

    // Should return count (0)
    ASSERT_EQ(0, array_find_first(data, count, 1));
}

// --- Test Suite 4: Array Sort (Callback) ---
// C-style comparator function for the test
int compare_ints(const void* a, const void* b) {
    const int arg1 = *static_cast<const int*>(a);
    const int arg2 = *static_cast<const int*>(b);

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

TEST(ArraySortTest, BasicIntegerSort) {
    int data[] = { 50, 10, 40, 20, 30 };
    size_t count = sizeof(data) / sizeof(data[0]);
    int expected[] = { 10, 20, 30, 40, 50 };

    int result = array_sort_c(data, count, sizeof(int), compare_ints);

    ASSERT_EQ(0, result);
    for (size_t i = 0; i < count; ++i) {
        ASSERT_EQ(expected[i], data[i]);
    }
}

// --- Test Suite 5: Logger Context Creation ---
TEST(LoggerTest, CreateWriteDestroy) {
    LoggerContext_t* handle = logger_create();

    ASSERT_NE(nullptr, handle);

    ASSERT_EQ(0, logger_write(handle, "First message."));
    ASSERT_EQ(0, logger_write(handle, "Second message."));

    ASSERT_EQ(-1, logger_write(nullptr, "Error message."));

    logger_destroy(handle);

}

TEST(LoggerTest, NullDestroyIsSafe) {
    ASSERT_NO_FATAL_FAILURE(logger_destroy(nullptr));
}