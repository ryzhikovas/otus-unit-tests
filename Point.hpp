#pragma once
#include <cstddef>
#include <tuple>
#include <ostream>

struct Point {
    size_t x;
    size_t y;
};

inline std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << "{" << p.x << ", " << p.y << "}";
}

inline bool operator<(const Point& lhs, const Point& rhs) {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

inline bool operator==(const Point& lhs, const Point& rhs) {
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

inline bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}