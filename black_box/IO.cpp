#include "IO.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace {
    const char lineSeparator = '\n';
    const char wall = 'X';
    const char space = ' ';
    const char start = 'S';
    const char destination = 'D';

    Map constructUnfilled(const std::string& s) {
        const char rowEnd = lineSeparator;
        const size_t height = std::count(s.begin(), s.end(), rowEnd);

        if (height == 0) {
            throw std::logic_error("Map::fromString: broken string: height == 0");
        }
        const size_t width = s.find(rowEnd);
        return {height, width};
    }
}

void print(const Map& m, Point start, Point destination) {
    std::ostream& out = std::cout;

    for (size_t i = 0; i < m.getHeight(); ++i) {
        for (size_t j = 0; j < m.getWidth(); ++j) {
            Point p = {j, i};
            const Cell cell = m.get(p);
            out << "|";

            if (p == start) {
                out << "S";
            } else if (p == destination) {
                out << "D";
            } else if (cell == Cell::Marker::Unused) {
                out << " ";
            } else if (cell == Cell::Marker::Wall) {
                out << "X";
            } else {
                out << cell.getId() << "";
            }
        }
        std::cout << "|" << std::endl;
    }
}

std::tuple<Map, Point, Point> fromString(const std::string& s) {
    Map m = constructUnfilled(s);

    if (s.size() != (m.getWidth() + 1) * m.getHeight()) {
        throw std::logic_error("Map::fromString: unexpected string size");
    }

    auto it = s.begin();

    std::optional<Point> startPos, destinationPos;
    for (size_t i = 0; i < m.getHeight(); ++i, ++it) {
        for (size_t j = 0; j < m.getWidth(); ++j, ++it) {
            char sym = *it;
            Point p = {j, i};

            if (sym == wall) {
                m.set(p, Cell::Marker::Wall);
            } else if (sym == start) {
                startPos = p;
            } else if (sym == destination) {
                destinationPos = p;
            } else if (sym != space) {
                throw std::logic_error("Map::fromString: broken string: unexpected symbol: " + std::string(1, sym));
            }
        }

        if (*it != lineSeparator) {
            throw std::logic_error("Map::fromString: broken string: eol not found");
        }
    }

    if (!startPos.has_value() || !destinationPos.has_value()) {
        throw std::logic_error("Map::fromString: can't detect start or destination pos");
    }
    return {m, startPos.value(), destinationPos.value()};
}