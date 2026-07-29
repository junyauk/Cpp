#include "pch.h"
#include "Caller.h"
#include <sstream>

import ModuleA;
import ModuleB;
import Legacy;
import ModuleT;

namespace moduleexample::caller
{

    // APIs using ModuleA functions -------------------------------------------

    int call_add(int a, int b)
    {
        return moduleexample::modulea::add(a,b);
    }

    std::string call_concat(const std::string& a, const std::string& b)
    {
        return moduleexample::modulea::concat(a,b);
    }

    int call_compute_value(int x)
    {
        return moduleexample::modulea::compute_value(x);
    }

    std::string call_get_message()
    {
        return moduleexample::modulea::message();
    }

    // APIs using both ModuleA and ModuleB ------------------------------------
    int call_add_both(int a, int b)
    {
        return moduleexample::modulea::add(a, b) + moduleexample::moduleb::add(a, b);
    }

    std::string call_concat_both(const std::string& a, const std::string& b)
    {
        return moduleexample::modulea::concat(a, b) + moduleexample::moduleb::concat(a, b);
    }

    int call_compute_value_both(int x)
    {
        return moduleexample::modulea::compute_value(x) + moduleexample::moduleb::compute_value(x);
    }

    std::string call_get_message_both()
    {
        return moduleexample::modulea::message() + " | " + moduleexample::moduleb::message();
    }

    // APIs using methods of Calculator calass --------------------------------

    int call_multiply(int a, int b)
    {
        // Calling ModuleA::Calculator::multiply (instance)
        moduleexample::modulea::Calculator calc;
        return calc.multiply(a, b);
    }

    std::string call_calculator_info()
    {
        // Calling ModuleA::Calculator::Info() (static)
        return moduleexample::modulea::Calculator::info();
    }

    int call_multiply_both(int a, int b)
    {
        moduleexample::modulea::Calculator calcA;
        moduleexample::moduleb::Calculator calcB;
        return calcA.multiply(a, b) + calcB.multiply(a, b);
    }

    std::string call_calculator_info_both()
    {
        return moduleexample::modulea::Calculator::info() + " & " + moduleexample::moduleb::Calculator::info();
    }

    // APIs using Legacy ------------------------------------------------------
    int call_legacy_add(int a, int b)
    {
        return moduleexample::legacy::legacy_add(a, b);
    }
    int call_legacy_multiply(int a, int b)
    {
        moduleexample::legacy::LegacyCalculator calc;
        return calc.multiply(a, b);
    }
    std::string call_legacy_calculator_info()
    {
        return moduleexample::legacy::LegacyCalculator::info();
    }

    // APIs using Legacy via ModuleA -----------------------------------------
    int call_legacy_add_viaModuleA(int a, int b)
    {
        return moduleexample::modulea::legacy_add_viaModuleA(a, b);
    }

    // APIs using Legacy via Calculator of ModuleA ----------------------------
    int call_calculator_legacy_multiply_viaModuleA(int a, int b)
    {
        moduleexample::modulea::Calculator calc;
        return calc.legacy_multiply(a, b);
    }

    std::string call_calculator_legacy_info_viaModuleA()
    {
        return moduleexample::modulea::Calculator::legacy_info();
    }

    // APIs using Legacy via ModuleB -----------------------------------------
    int call_legacy_add_viaModuleB(int a, int b)
    {
        return moduleexample::moduleb::legacy_add_viaModuleB(a, b);
    }

    // APIs using Legacy via Calculator of ModuleB ----------------------------
    int call_calculator_legacy_multiply_viaModuleB(int a, int b)
    {
        moduleexample::moduleb::Calculator calc;
        return calc.legacy_multiply(a, b);
    }

    std::string call_calculator_legacy_info_viaModuleB()
    {
        return moduleexample::moduleb::Calculator::legacy_info();
    }

    // API combining constants of Legacy and ModuleA --------------------------
    std::string get_combined_values_string()
    {
        std::ostringstream oss;
        oss << "ModuleA: " << moduleexample::modulea::kModuleAValue
            << ", Legacy: " << moduleexample::legacy::kLegacyValue
            << ", Combined: " << moduleexample::modulea::kModuleACombinedValue;
        return oss.str();
    }


    std::string call_pair_int_to_string(int a, int b)
    {
        return moduleexample::modulet::Pair<int, int>(a, b).to_string();
    }
    std::string call_pair_string_int_to_string(const std::string& s, int n)
    {
        return moduleexample::modulet::Pair<const std::string, int>(s, n).to_string();
    }

	// ------------------------------------------------------------------------
    NumberInfo GetIntNumberInfo(int v)
    {
		auto p = moduleexample::modulet::CreateIntNumberProvider(v);
		return { p->getValue() };
    }
    NumberInfo GetStringNumberInfo(const std::string& s)
    {
		auto p = moduleexample::modulet::CreateStringNumberProvider(s);
		return { p->getValue() };
    }


}



// using templates from TemplateA and TemplateB
import templatea;
import templateb;

int addInt(int a, int b)
{
	return add(a, b);
}
double mulDouble(double a, double b)
{
	return mul(a, b);
}
int addThenMulInt(int a, int b, int c)
{
	return add_then_mul(a, b, c);
}

// add using doulbe/float hasn't been instantiated in modules
// float fsum = add(1.0f, 2.0f); 


