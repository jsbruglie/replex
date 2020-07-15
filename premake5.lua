workspace "RePlex"
  configurations {"Debug", "Release"}
  -- Use C++ as the target language for all builds
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  -- Get that C++14 goodness
  cppdialect "C++14"

  filter "configurations:Debug"
    -- Add the preprocessor definition DEBUG to debug builds
    defines { "DEBUG" }
    -- Ensure symbols are bundled with debug builds
    symbols "On"

  filter "configurations:Release"
    -- Add the preprocessor definition RELEASE to debug builds
    defines { "RELEASE" }
    -- Turn on compiler optimizations for release builds
    optimize "On"

  -- RePlex Runtime
  project "RePlexRuntime"
    kind "ConsoleApp"
    -- recursively glob .h and .cpp files in the runtime directory
    files { "runtime/**.h", "runtime/**.cpp" }
    includedirs { "lib/include", "foo/include" }
    links { "dl" }

  -- RePlex test library
  project "RePlexFoo"
    kind "SharedLib"
    files { "foo/**.h", "foo/**.cpp", "foo/include/*.h" }
    includedirs { "lib/include" }
    links { "dl" }

  -- Google Test
  project "GoogleTest"
    kind "StaticLib"
    files { "googletest/googletest/src/gtest-all.cc" }
    includedirs { "googletest/googletest/include", "googletest/googletest" }

  project "TestRePlexFoo"
    kind "ConsoleApp"
    files { "test/**.h", "test/**.cpp" }
    includedirs { "lib/include", "foo/include", "googletest/googletest/include" }
    links { "GoogleTest", "pthread", "dl" }
