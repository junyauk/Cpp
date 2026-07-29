#include "pch.h"
#include "gtest/gtest.h"
#include "..\00_Concepts\Concepts_Advanced.h"

using Concepts_Advance::LogDataStore;
using Concepts_Advance::UserProfile;

namespace Concepts_Advance_Test
{
	class ConceptsAdvanceTest : public ::testing::Test {};

    TEST_F(ConceptsAdvanceTest, Store_Accepts_LoggableData)
    {
        // UserProfile satisfies LoggableData (HasID and Printable)
        LogDataStore<UserProfile> user_logger;
        user_logger.addRecord({ 1, "Alice" });
        user_logger.addRecord({ 2, "Bob" });

        EXPECT_EQ(2, user_logger.count());

        std::string log = user_logger.dump_log();

        // Verify output uses the guaranteed to_string and id access
        EXPECT_NE(std::string::npos, log.find("LOG_ENTRY (ID=1): [ID:1] User: Alice"));
        EXPECT_NE(std::string::npos, log.find("LOG_ENTRY (ID=2): [ID:1] User: Bob"));
    }

    // --- Conceptual Test: Rejection (Will cause a COMPILER ERROR) ---
    /*
    struct NonLoggable { // Missing 'id' member and 'to_string'
        int data;
    };

    TEST_F(ConceptsAdvancedTest, Store_Rejects_NonLoggableData)
    {
        // UNCOMMENTING THE LINE BELOW WILL CAUSE A COMPILE-TIME ERROR:
        // LogDataStore<NonLoggable> invalid_logger;
        SUCCEED() << "Non-Loggable data is conceptually rejected at compile time.";
    }
    */
}
