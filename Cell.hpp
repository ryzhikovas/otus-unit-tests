#pragma once
#include <cstddef>
#include <limits>
#include <optional>

class Cell {
public:
    enum Marker : size_t {
        Start = 0,
        Unused = std::numeric_limits<size_t>::max() - 1,
        Wall = std::numeric_limits<size_t>::max()
    };

public:
    Cell(Marker marker);
    Cell next() const;
    bool operator==(Cell other) const;
    size_t getId() const;
private:
    Cell(size_t id);

private:
    size_t id;
};

inline Cell::Cell(Marker marker) : Cell(static_cast<size_t>(marker)) {}

inline Cell Cell::next() const { return {id + 1}; }

inline bool Cell::operator==(Cell other) const {
    return id == other.id;
}

inline Cell::Cell(size_t id) : id{id} {}

inline size_t Cell::getId() const { return id; }
