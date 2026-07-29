#pragma once
#include <string>
#include <iostream>

namespace DesignatedInit_Basic
{
    /**
     * @brief An aggregate structure suitable for designated initialization.
     */
    struct UserSettings
    {
        int m_id;
        bool m_darkMode;
        std::string m_language;
        int m_fontSize;
    };

    /**
     * @brief Utility class to demonstrate designated initialization.
     */
    class DesignatedInitBasic
    {
    public:
        DesignatedInitBasic() = default;

        /**
         * @brief Initializes UserSettings using designated initializers, ensuring clarity.
         * @return A UserSettings object initialized using designated initializers.
         */
        UserSettings createFullSettings() const
        {
            // Designated Initializers: Members must be specified in the order of declaration.
            UserSettings settings =
            {
                .m_id = 101,            // 1st member
                .m_darkMode = true,     // 2nd member
                .m_language = "English",// 3rd member
                .m_fontSize = 12        // 4th member
            };
            return settings;
        }

        /**
         * @brief Initializes UserSettings partially, relying on default initialization for the rest.
         * @return A partially initialized UserSettings object.
         */
        UserSettings createPartialSettings() const
        {
            // Partial initialization: m_id and m_darkMode are initialized.
            // m_language and m_fontSize are default initialized (empty string and 0).
            UserSettings settings =
            {
                .m_id = 202,        // 1st member
                .m_darkMode = false // 2nd member
                // m_language and m_fontSize are implicitly default initialized.
            };
            return settings;
        }

        UserSettings createPartialSettingsOK() const
        {
            // Partial initialization: m_darkMode and m_fontSize are initialized.
            // m_id and m_language are default initialized (empty string and 0).
            UserSettings settings =
            {
//                .m_id = 303,          // 1st member
                .m_darkMode = true,     // 2nd member
//                .m_language = "English",// 3rd member
                .m_fontSize = 40        // 4th member
            };
            return settings;
        }

/*
        // NOTE:
        // Order of members needs to be the same as defined.
        UserSettings createPartialSettingsNG() const
        {
            // Partial initialization: m_darkMode and m_fontSize are initialized.
            // m_id and m_language are default initialized (empty string and 0).
            UserSettings settings =
            {
                // !!! NG order !!!
                .m_fontSize = 12,       // 4th member
                .m_language = "English",// 3rd member
                .m_darkMode = true,     // 2nd member
                .m_id = 101             // 1st member
            };
            return settings;
        }
*/
        /**
         * @brief Demonstrates the mandatory ordered initialization (if order is violated, it's an error).
         * NOTE: The compiler will enforce that designated initializers appear in the order
         * of member declaration.
         */


    };


}
