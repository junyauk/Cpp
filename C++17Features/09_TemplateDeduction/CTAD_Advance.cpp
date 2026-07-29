#include "pch.h"
#include "CTAD_Advance.h"

namespace CTAD_Advance
{
    // 2. Application: Standard Library Check
    std::map<int, std::string> CTAD_Advance::createStandardMap()
    {
        // C++17 CTAD: std::map<int, std::string> can be simplified
        // Key=int, Value=std::string can be deduced from pairs { {1, "A"}, {2, "B"} }
        std::map m =
        {
            std::pair{1, "Apple"}, // types in the std::pair can be deduced
            std::pair{2, "Banana"}
        };

        // it can be deduced...
        std::map<int, std::string> m2 =
        {
/*
            {3, "Cherry"},
            {4, "Date"}
*/
            {3, "Cherry"},
            {4, "Date"}
        };
        return m2;
    }

    // 1. Application: User-Defined Class Check
    MyVector<int> CTAD_Advance::createCustomVector()
    {
        // Doesn't need to write MyVector<int>
        // Initializer List Constructor (deduction guide is used implicitly/explicitly)
        MyVector vec = { 10, 20,30,40 };
        return vec;
    }
}
