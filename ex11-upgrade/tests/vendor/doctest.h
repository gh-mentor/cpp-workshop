// Minimal embedded doctest single header (trimmed for brevity in this educational scaffold)
#pragma once
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace doctest {
    using TestFunc = void(*)();
    struct TestRegistry { std::vector<std::pair<std::string, TestFunc>> tests; static TestRegistry& inst(){ static TestRegistry r; return r;} };
    struct Register { Register(const char* n, TestFunc f){ TestRegistry::inst().tests.push_back({n,f}); } };
    struct AssertException: std::exception { const char* what() const noexcept override { return "assertion failed"; } };
}

#define TEST_CASE(name) static void name(); static doctest::Register reg_##name(#name, &name); static void name()
#define REQUIRE(cond) do { if(!(cond)) { std::cerr << "Requirement failed: " #cond " at " << __FILE__ << ":" << __LINE__ << "\n"; throw doctest::AssertException(); } } while(0)

int main(){
    int fails=0; 
    for(auto& tc: doctest::TestRegistry::inst().tests){
        try { tc.second(); std::cout << "[PASS] " << tc.first << "\n"; }
        catch(...) { std::cout << "[FAIL] " << tc.first << "\n"; ++fails; }
    }
    std::cout << doctest::TestRegistry::inst().tests.size() - fails << "/" << doctest::TestRegistry::inst().tests.size() << " tests passed\n";
    return fails==0?0:1;
}
