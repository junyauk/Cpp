#include "pch.h"
#include <iostream>
#include "ConstexprLambda_Advance.h"

namespace CONSTEXPRLAMBDA_Advance
{
    // Source file must define the static constexpr members if they are ODR-used
    // (though often not strictly necessary if used only in a constexpr context).
    // We define them here to ensure ODR-use compliance and link success.

//    constexpr int ConstexprLambda_Advance::Config::MAX_VALUE;
//    constexpr std::array<int, 3> ConstexprLambda_Advance::Config::DATA_PATTERN;

    // No runtime logic needed in the source file for these compile-time functions.
}
