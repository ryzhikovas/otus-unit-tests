#include <gtest/gtest.h>
#include "../Cell.hpp"

TEST(cell_test, cell_indexes_order) {
    Cell cell(Cell::Start);
    EXPECT_EQ(cell.getId(), 0);

    Cell second = cell.next();
    EXPECT_EQ(second.getId(), 1);

    EXPECT_EQ(second.next().getId(), 2);
}