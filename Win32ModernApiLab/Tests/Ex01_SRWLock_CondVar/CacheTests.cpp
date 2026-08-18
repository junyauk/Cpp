#include "gtest/gtest.h"
#include "gtest/gtest-typed-test.h"

#include "classicmutexcache.h"
#include "modernsrwcache.h"
using namespace Ex01_SRWLock_CondVar;

namespace Ex01_SRWLock_CondVarTests
{
	template<typename T>
	class CacheTest : public ::testing::Test
	{
	};

	using CacheImplementations = ::testing::Types<ClassicMutexCache, ModernSrwCache>;

	TYPED_TEST_CASE(CacheTest, CacheImplementations);

	TYPED_TEST(CacheTest, GetCapacity)
	{
		TypeParam cache(2);
		EXPECT_EQ(cache.GetCapacity(), 2);
		cache.Put("key1", "value1");
		cache.Put("key2", "value2");
		EXPECT_EQ(cache.GetCapacity(), 2);
	}

	TYPED_TEST(CacheTest, GetNonExistentKey)
	{
		TypeParam cache(2);
		std::string value;
		EXPECT_FALSE(cache.Get("key1", value)); // Getting a non-existent key should return false
	}

	TYPED_TEST(CacheTest, RemoveNonExistentKey)
	{
		TypeParam cache(2);
		cache.Put("key1", "value1");
		cache.Remove("key2"); // Removing a non-existent key should not cause issues
		std::string value;
		EXPECT_TRUE(cache.Get("key1", value));
		EXPECT_EQ(value, "value1");
	}

	TYPED_TEST(CacheTest, BasicFunctionality)
	{
		TypeParam cache(2);
		std::string value;
		cache.Put("key1", "value1");
		EXPECT_EQ(1, cache.GetCount());
		cache.Put("key2", "value2");
		EXPECT_EQ(2, cache.GetCount());
		EXPECT_TRUE(cache.Get("key1", value));
		EXPECT_EQ(value, "value1");
		EXPECT_EQ(2, cache.GetCount());
		EXPECT_TRUE(cache.Get("key2", value));
		EXPECT_EQ(value, "value2");
		EXPECT_EQ(2, cache.GetCount());
		cache.Remove("key1");
		EXPECT_EQ(1, cache.GetCount());
		EXPECT_FALSE(cache.Get("key1", value));
	}

	TYPED_TEST(CacheTest, CapacityLimit)
	{
		TypeParam cache(2);
		cache.Put("key1", "value1");
		cache.Put("key2", "value2");
		std::thread t([&cache]() {
			cache.Put("key3", "value3"); // This should block until a key is removed
			});
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Give time for the thread to start and block
		cache.Remove("key1"); // This should unblock the thread
		t.join();
		std::string value;
		EXPECT_TRUE(cache.Get("key3", value));
		EXPECT_EQ(value, "value3");
	}

	TYPED_TEST(CacheTest, RemoveAndPut)
	{
		TypeParam cache(2);
		cache.Put("key1", "value1");
		cache.Put("key2", "value2");
		cache.Remove("key1");
		cache.Put("key3", "value3"); // This should not block since we removed a key
		std::string value;
		EXPECT_TRUE(cache.Get("key3", value));
		EXPECT_EQ(value, "value3");
	}

}
