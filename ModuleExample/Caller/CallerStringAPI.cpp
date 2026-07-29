#include "pch.h"
#include "CallerStringAPI.h"

import stringutils;

std::string caller_to_upper(const std::string& input)
{
	return to_upper(input); // in StringUtils module
}

std::string caller_to_lower(const std::string& input)
{
	return to_lower(input);	// in StringUtils module
}
