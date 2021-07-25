#include <gtest/gtest.h>
#include "../point_distance.hpp"

// adding a test fixture
struct MainTests : public ::testing::Test
{
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    Point p5;
    Point p6;
    Point p7;
    pointPair smallestDistancePair;
    pointPair biggestDistancePair;
    PointsOperations distanceCalculator;
    std::vector<Point> testPoints = {};
    // usually we overload SetUp and TearDown
    virtual void SetUp() override
    {
        p1 = {1, 4};
        p2 = {4, 4};
        p3 = {5, 1};
        p4 = {3, 2};
        p5 = {22, 21};
        p6 = {-1, -2};
        p7 = {9, 14};
        testPoints = {p1, p2, p3, p4, p6, p7, p5};
        smallestDistancePair = {p2, p4};
        biggestDistancePair =  {p6, p5};
    }

    virtual void TearDown() override
    {}
};

TEST_F(MainTests, testDistance)
{
    // this is just a sample test that passes
    ASSERT_TRUE(distanceCalculator.distance(p1, p2) < distanceCalculator.distance(p2, p3));
    ASSERT_TRUE(distanceCalculator.distance(p1, p3) > distanceCalculator.distance(p2, p3));
    ASSERT_FALSE(distanceCalculator.distance(p3, p2) < distanceCalculator.distance(p2, p1));
}

TEST_F(MainTests, testSmallestDistance)
{
    ASSERT_EQ(distanceCalculator.calculateDistance(testPoints, [](double x, double y){ return x > y; }), smallestDistancePair);
}

TEST_F(MainTests, testBiggestDistance)
{
    ASSERT_EQ(distanceCalculator.calculateDistance(testPoints, [](double x, double y){ return x < y; }), biggestDistancePair);
}

TEST_F(MainTests, testMinMax)
{
    auto result = distanceCalculator.calculateMinMaxDistance(testPoints);
    ASSERT_EQ(result.first, smallestDistancePair);
    ASSERT_EQ(result.second, biggestDistancePair);
}