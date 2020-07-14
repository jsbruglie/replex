#include <RePlex.h>

#include <iostream>

// Path to built test library
#ifdef DEBUG
const char* g_libPath = "bin/Debug/libRePlexTest.so";
#else
const char* g_libPath = "bin/Release/libRePlexTest.so";
#endif

// Function pointer
void (*foo)();

int main()
{
	// Load test library and store handle
    void* handle = Load(g_libPath);
    if (!handle)
    {
    	PrintError();
    	return 1;
    }

    // Set the memory address of the function foo from the library to our foo.
    // reinterpret_cast indicates LoadSymbol returns a pointer to a function
    // (not just a generic void* pointer)
    foo = reinterpret_cast<void (*)()>(LoadSymbol(handle, "foo"));
    // Call foo
    foo();

    return 0;
}
