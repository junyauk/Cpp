#pragma once
#include <string>

namespace moduleexample::caller
{
    // APIs using ModuleA
    int call_add(int a, int b);
    std::string call_concat(const std::string& a, const std::string& b);
    int call_compute_value(int x);
    std::string call_get_message();
    int call_multiply(int a, int b);
    std::string call_calculator_info();

    // APIs using both ModuleA and ModuleB
    int call_add_both(int a, int b);
    std::string call_concat_both(const std::string& a, const std::string& b);
    int call_compute_value_both(int x);
    std::string call_get_message_both();
    int call_multiply_both(int a, int b);
    std::string call_calculator_info_both();

    // APIs using Calculator in Legacy as it is
    int call_legacy_add(int a, int b);
    int call_legacy_multiply(int a, int b);
    std::string call_legacy_calculator_info();

    // APIs using Legacy via ModuleA
    int call_legacy_add_viaModuleA(int a, int b);
    // APIs using Legacy via Calculator of ModuleA
    int call_calculator_legacy_multiply_viaModuleA(int a, int b);
    std::string call_calculator_legacy_info_viaModuleA();

    // APIs using Legacy via ModuleB
    int call_legacy_add_viaModuleB(int a, int b);
    // APIs using Legacy via Calculator of ModuleB
    int call_calculator_legacy_multiply_viaModuleB(int a, int b);
    std::string call_calculator_legacy_info_viaModuleB();

    // API combining constants of Legacy and ModuleA
    std::string get_combined_values_string();

    template<typename T>
    T call_twice(T v)
    {
        return v * 2;
    }

    std::string call_pair_int_to_string(int a, int b);
    std::string call_pair_string_int_to_string(const std::string& s, int n);


    // ------------------------------------------------------------------------
    struct NumberInfo
    {
        size_t value;
    };

    NumberInfo GetIntNumberInfo(int v);
    NumberInfo GetStringNumberInfo(const std::string& s);
}

// using templates from TemplateA and TemplateB
import templatea;
import templateb;

int addInt(int a, int b);
double mulDouble(double a, double b);
int addThenMulInt(int a, int b, int c);

