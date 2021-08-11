#include <gtest/gtest.h>

// adding a test fixture
struct MainTests : public ::testing::Test
{
    // usually we overload SetUp and TearDown
    virtual void SetUp() override
    {

    }

    virtual void TearDown() override
    {

    }
};

TEST_F(MainTests, test1)
{
    // this is just a sample test that passes
    ASSERT_EQ(true, true);
}