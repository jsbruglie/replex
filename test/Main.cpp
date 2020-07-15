#include <RePlex.h>
#include <FooModule.h>

#include <cstdlib>
#include <fstream>

#include <gtest/gtest.h>

const char* g_Test_v1 =
    "#include \"include/FooModule.h\"\n"
    "int bar = 42;\n"
    "int foo(int x) { return x + 5; }";

const char* g_Test_v2 =
    "#include \"include/FooModule.h\"\n"
    "int bar = -2;\n"
    "int foo(int x) { return x - 5; }";

/// @brief Fixture class
class RePlexTest : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        WriteFile("foo/FooModule.cpp", g_Test_v1);
        Compile(1);
        FooModule::LoadLibrary();
    }

    void ChangeAndReload()
    {
        WriteFile("foo/FooModule.cpp", g_Test_v2);
        Compile(2);
        FooModule::ReloadLibrary();
    }

    virtual void TearDown()
    {
        FooModule::UnloadLibrary();
        WriteFile("foo/FooModule.cpp", g_Test_v1);
        Compile(1);
    }

private:

    // Currently compiled version of FooModule.cpp
    int m_version = 1;

    void WriteFile(const char* path, const char* content)
    {
        // Output file stream and delete existing output
        std::ofstream out(path, std::ios_base::out);
        out << content;
    }

    void Compile(int version)
    {
        // Skip compiling if current version is the same
        if (version == m_version)
            return;

        EXPECT_EQ(std::system("make"), 0);
        sleep(1);
        m_version = version;
    }
};

// Concrete test cases

/// @brief test if GetBar() is reloaded
TEST_F(RePlexTest, VariableReload)
{
    EXPECT_EQ(FooModule::GetBar(), 42);
    ChangeAndReload();
    EXPECT_EQ(FooModule::GetBar(), -2);
}

/// @brief Test if Foo() is reloaded
TEST_F(RePlexTest, FunctionReload)
{
    EXPECT_EQ(FooModule::Foo(4), 9);
    ChangeAndReload();
    EXPECT_EQ(FooModule::Foo(4), -1);
}

int main(int argc, char** argv)
{
    // Allows us to pass command-line arguments to InitGoogleTest
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
