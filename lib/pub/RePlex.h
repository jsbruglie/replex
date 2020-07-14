#pragma once

#include <dlfcn.h>

/// Loads library into memory
///
/// @param filepath Path to library to load
/// @return Pointer to loaded library
void* Load(const char* filepath);

/// Loads symbol from library into memory
///
/// @param library Pointer to loaded library
/// @param symbol Name of symbol to load
/// @return Pointer to loaded symbol
void* LoadSymbol(void* library, const char* symbol);

/// Closes loaded library and reloads it
///
/// @param library Pointer to loaded library
/// @param filepath Path to library to reload
void Reload(void* &library, const char* filepath);

/// Prints the last library/symbol loading related error
void PrintError();
