#pragma once
#include <format>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

namespace Formatting_Basic
{
    /**
     * @brief Defines common time and date formatting presets.
     */
    enum class TimeFormat {
        DateOnly,       // YYYY-MM-DD
        Time24Hour,     // HH:MM:SS
        Time12Hour,     // HH:MM:SS AM/PM
        FullDateTime24, // YYYY-MM-DD HH:MM:SS
        FullDateTime12  // YYYY-MM-DD HH:MM:SS AM/PM
    };

    /**
     * @brief Utility class to demonstrate C++20 formatting features (std::format).
     */
    class FormattingBasic
    {
    public:
        FormattingBasic() = default;

        /**
         * @brief Demonstrates basic formatting with implicit argument indexing.
         * @param name Name string.
         * @param version Version number.
         * @return Formatted string.
         */
        std::string formatBasic(const std::string& name, int version) const
        {
            // Implicit indexing: Arguments are placed in order of appearance
            return std::format("{} Version {}", name, version);
        }

        /**
         * @brief Demonstrates advanced numerical formatting (precision, base, sign).
         * @param pi The value of Pi.
         * @param number A negative integer.
         * @return Formatted string.
         */
        std::string formatNumbers(double pi, int number) const
        {
            // 1. Fixed point with 4 decimal places: {:.4f}
            // 2. Binary representation with prefix: {#b}
            // 3. Sign prefix: {:+}
            return std::format("Pi: {:.4f}, Binary: {:b}, Sign: {:+}", pi, number, number);
        }

        /**
         * @brief Demonstrates padding, alignment, and width specification.
         * @param item A string to align.
         * @param price A float price value.
         * @return Formatted string using alignment.
         */
        std::string formatAlignment(const std::string& item, float price) const
        {
            // 1. Item: Width 15, left-aligned, padded with '-': {:<15}
            // 2. Price: Width 8, right-aligned, padded with '*': {:*>8.2f}
            return std::format("{:-<15} | {:*>8.2f}", item, price);

        }

        /**
         * @brief Demonstrates formatting standard library types (chrono) using a predefined enum.
         * This uses std::format for compile-time safety.
         * @param formatType The desired time format from the TimeFormat enum.
         * @return Formatted time string.
         */
        std::string formatChrono(TimeFormat formatType) const
        {
            auto now = std::chrono::system_clock::now();

            // Convert to time_t and then to tm structure for component access
            // C++20 prefers <chrono> functions for this, but tm struct is often simpler for formatting components.
            auto now_t = std::chrono::system_clock::to_time_t(now);
            struct tm local_time;
            // Use thread-safe localtime_s/localtime_r if available, otherwise std::localtime
#ifdef _WIN32
            localtime_s(&local_time, &now_t);
#else
            localtime_r(&now_t, &local_time);
#endif
            // Base format string without seconds/minutes/hours for manual formatting
            std::string date_part;
            std::string time_part;

            // Use static format strings based on the enum for compile-time safety
            switch (formatType)
            {
            case TimeFormat::DateOnly:
                return std::format("{:%Y-%m-%d}", now); // Date is usually safe

            // Manual formatting: Hour (02), Minute (02), Second (02)
            // Otherwise, std::format will output seconds part longer than XX.
            case TimeFormat::FullDateTime24:
                date_part = std::format("{:%Y-%m-%d} ", now);
                [[fallthrough]];
            case TimeFormat::Time24Hour:
                time_part = std::format("{:02}:{:02}:{:02}",
                    local_time.tm_hour, // hours
                    local_time.tm_min,  // mins
                    local_time.tm_sec); // secs
                break;

            case TimeFormat::FullDateTime12:
                date_part = std::format("{:%Y-%m-%d} ", now);
                [[fallthrough]];
            case TimeFormat::Time12Hour:
                time_part = std::format("{:02}:{:02}:{:02} {}", 
                    (local_time.tm_hour % 12) ? 12 : (local_time.tm_hour % 12), // hours
                    local_time.tm_min,                                          // mins
                    local_time.tm_sec,                                          // secs
                    (local_time.tm_hour > 12) ? "PM" : "AM");                   // AM/PM
                break;
            default:
                // Should not happen, but ensures all paths return a value
                throw std::runtime_error("Unknown TimeFormat type.");
            }

            return date_part + time_part;
        }
    };


}
