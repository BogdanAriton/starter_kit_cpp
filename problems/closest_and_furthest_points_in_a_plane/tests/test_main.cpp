#include <gtest/gtest.h>
#include "../myproject.hpp"

// adding a test fixture
struct MainTests : public ::testing::Test
{
    // usually we overload SetUp and TearDown
    PointHandler pointHandler;
    std::vector<Point> points = {};
    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {

    }
};

TEST_F(MainTests, happyPathMax)
{
    points = {{1, 4}, {4,4}, {3,2}, {5,1}};
    std::pair<Point, Point> expecteedMaxPair = {{1, 4},{5,1}};
    auto result = pointHandler.calcultateDistance(points);

    ASSERT_EQ(result.max.first, expecteedMaxPair.first);
    ASSERT_EQ(result.max.second, expecteedMaxPair.second);
}

TEST_F(MainTests, happyPathMin)
{
    points = {{1, 4}, {4,4}, {3,2}, {5,1}};
    std::pair<Point, Point> expectedMinPair = {{4,4}, {3,2}};
    auto result = pointHandler.calcultateDistance(points);

    ASSERT_EQ(result.min.first, expectedMinPair.first);
    ASSERT_EQ(result.min.second, expectedMinPair.second);
}