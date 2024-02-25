#include "Map.hpp"
#include <cmath>

Map::Map(size_t height, size_t width)
    : width{width}, height{height},
      cells(height * width, Cell::Marker::Unused) {}

Cell Map::get(Point pos) const {
    return cells[mapPosToOffset(pos)];
}

void Map::set(Point pos, const Cell &cell) {
    cells[mapPosToOffset(pos)] = cell;
}

void Map::forEachNeighbor(Point pos, std::function<bool(Point)> callback) const {
    const size_t padding = 1;
    auto forEachInWindow = [=] (size_t pos, size_t rightBorder, auto callback) {
        const size_t min = std::max(pos, padding) - padding;

        const size_t max = std::min(
            std::min(pos, rightBorder - padding) + padding + 1, // warning: maybe size_t overflow
            rightBorder
        );

        for (size_t i = min; i < max; ++i) {
            callback(i);
        }
    };

    bool stop = false;
    forEachInWindow(pos.y, height, [&] (size_t y) {
        forEachInWindow(pos.x, width, [&] (size_t x) {
            Point p{x, y};

            if (p != pos && !stop) {
                stop = !callback(p);
            }
        });
    });
}

size_t Map::getWidth() const { return width; }

size_t Map::getHeight() const { return height; }

size_t Map::mapPosToOffset(Point pos) const {
    return pos.y * width + pos.x;
}
