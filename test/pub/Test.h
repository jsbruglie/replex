#pragma once

#include <RePlex.h>

// Prevents C++ name mangling which would prevent dlsym from retrieving
// the correct symbols.
extern "C"
{
    int foo(int);
    // The extern keyword here exports a global variable that will be defined in Test.cpp
    extern int bar;
}

// Array with symbol, address pairs
std::array<std::pair<const char*, void*>, 2> g_exports = {
    std::make_pair("foo", nullptr),
    std::make_pair("bar", nullptr)
};

/// @brief Concrete library which can be hot reloaded
class TestModule : public RePlexModule<TestModule, g_exports.size()>
{
public:

    TestModule() : RePlexModule(g_exports) {}

    static int Foo(int input)
    {
        return GetInstance().Execute<0, int, int>(input);
    }

    static int GetBar()
    {
        // decltype operator returns an entity's static type (compile-time)
        // decltype(bar) = int
        return *GetInstance().GetVar<1, decltype(bar)>();
    }

protected:

    virtual const char* GetPath() const override
    {
#ifdef DEBUG
        return "bin/Debug/libRePlexTest.so";
#else
        return "bin/Release/libRePlexTest.so";
#endif
    }
};
