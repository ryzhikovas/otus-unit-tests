#pragma once
#include <array>
#include <functional>
#include <vector>
#include "Cell.hpp"
#include "Point.hpp"

class Map {
public:
    Map(size_t height, size_t width);
    Cell get(Point pos) const;
    void set(Point pos, const Cell& cell);
    void forEachNeighbor(Point pos, std::function<bool (Point)> callback) const;
    size_t getWidth() const;
    size_t getHeight() const;
private:
    size_t mapPosToOffset(Point pos) const;
private:
    size_t width;
    size_t height;
    std::vector<Cell> cells;
};
