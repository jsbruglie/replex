#include <gtest/gtest.h>

TEST(DummyTest, IsFourPositive)
{
	EXPECT_GT(4, 0);
}

TEST(DummyTest, IsFourTimesSixteen)
{
	int x = 4;
	EXPECT_EQ(x * x, 16);
}

int main(int argc, char** argv)
{
	// Allows us to pass command-line arguments to InitGoogleTest
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
