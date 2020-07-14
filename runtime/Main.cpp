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

    // Read the data from the global variable bar in the test library
    int bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
    std::cout << "bar == " << bar << std::endl;

    // Wait for input to give us a chance to recompile the library
    std::cout << "Make some changes, recompile, and press enter." << std::flush;
    while(std::cin.get() != '\n') {}

    // Reload the library!
    Reload(handle, g_libPath);

    // We need to refetch the symbol because it's location in memory may have changed
    foo = reinterpret_cast<void (*)()>(LoadSymbol(handle, "foo"));
    foo();

    // Do the same for bar
    bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
    std::cout << "bar == " << bar << std::endl;

    return 0;
}
