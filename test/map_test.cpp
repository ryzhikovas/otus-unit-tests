#include "../Map.hpp"
#include <gtest/gtest.h>

// TODO: empty map?

TEST(map_test, construction) {
    Map map(2, 3);

    ASSERT_EQ(map.getWidth(), 3);
    ASSERT_EQ(map.getHeight(), 2);

    for (size_t i = 0; i < map.getHeight(); ++i) {
        for (size_t j = 0; j < map.getWidth(); ++j) {
            EXPECT_EQ(map.get({j, i}), Cell::Marker::Unused);
        }
    }
}

TEST(map_test, access) {
    Map map(3, 2);
    Point p{2, 1};

    map.set(p, Cell::Marker::Start);

    EXPECT_EQ(map.get(p), Cell::Marker::Start);
}

TEST(map_test, DISABLED_out_of_bound) {
    Map map(3, 2);
    Point p{4, 5};

    EXPECT_ANY_THROW(map.set(p, Cell::Marker::Start));

    EXPECT_ANY_THROW(map.get(p));
}

TEST(map_test, neigbors_of_middle_cell) {
    Map map(4, 3);
    Point p{1, 2};

    std::set<Point> points;
    map.forEachNeighbor(p, [&](Point p) {
        points.insert(p);
        return true;
    });

    std::set expected = {Point{0, 1}, {1, 1}, {2, 1}, {0, 2}, {2, 2}, {0, 3}, {1, 3}, {2, 3}};

    EXPECT_EQ(points, expected);
}

TEST(map_test, neigbors_of_single_element_map) {
    Map map(1, 1);
    Point p{0, 0};

    std::set<Point> points;
    map.forEachNeighbor(p, [&](Point p) {
        points.insert(p);
        return true;
    });

    EXPECT_TRUE(points.empty());
}

TEST(map_test, neigbors_of_bound_cell) {
    Map map(3, 3);

    {
        // Уберем дублирование forEachNeighbor
        std::set<Point> points;
        map.forEachNeighbor({0, 0}, [&] (Point p) {
            points.insert(p);
            return true;
        });

        std::set expected = {Point{0, 1}, {1, 1}, {1, 0}};
        EXPECT_EQ(points, expected);
    }

    {
        std::set<Point> points;
        map.forEachNeighbor({2, 2}, [&] (Point p) {
            points.insert(p);
            return true;
        });

        std::set expected = {Point{1, 2}, {1, 1}, {2, 1}};
        EXPECT_EQ(points, expected);
    }
}
