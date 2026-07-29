#include "pch.h"
#include "framework.h"
#include "InlineVariables_Basic.h"

namespace INLINEVARIABLES_Basic
{
	int InlineVariables_Basic::getDefaultTimeout() const
	{
		// Access the inline map defined in the header
		auto it = CONFIG_DEFAULT.find("Timeout");
		if (it != CONFIG_DEFAULT.end())
		{
			return it->second;
		}
		return 0;
	}

	int InlineVariables_Basic::getCurrentCountAndInstance() const
	{
		// Read the count before creating an instance
		int initialCount = Counter::instanceCount;

		// Create a local instance which increments the inline static variable
		Counter temp_c;

		// temp_c goes out of scope immediately, so the count is the initial count.
		// We return the count *after* increment/decrement for demonstration.
		// For testing, we'll rely on the test code to create external instances.

		// Return the count *before* the function's side effect is complete
		return initialCount;
	}

	// -------------------------------------------------------------------------
	// NOTE: 
	// If this file were to include a non-inline global variable defined in the 
	// header (without 'extern'), it would cause a linker error due to ODR violation.
	// Since all shared variables are 'inline', this CPP file compiles and links 
	// correctly with other CPP files that include the same header.
	// -------------------------------------------------------------------------

	// We add a dummy function to simulate another translation unit accessing the variable
	// This helps ensure the linker correctly resolves the single instance.
	int access_inline_counter()
	{
		INLINEVARIABLES_Basic::Counter dummy_counter;
		return INLINEVARIABLES_Basic::Counter::instanceCount;
	}

	int get_inline_timeout()
	{
		return INLINEVARIABLES_Basic::CONFIG_DEFAULT.at("Timeout");
	}
}
