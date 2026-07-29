#include "pch.h"
#include "framework.h"

// Fold expressions are highly dependent on templates, and their bodies are 
// often entirely contained within the header file (as is the case here).
// The source file is primarily for non-template definitions, or to ensure 
// the static library links correctly.

namespace FOLDEXPRESSIONS_Basic
{
    // No implementation needed here as all methods are template functions
    // implemented directly in the header file.
}
