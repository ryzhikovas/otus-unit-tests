#include <iostream>
#include <set>
#include <utility>
#include "black_box/IO.hpp"
#include "Map.hpp"

bool waveExpansion(Map& map, Point start, Point destination) {
    std::set<Point> wave = {start};
    std::set<Point> nextWave;
    Cell current = Cell::Marker::Start;

    bool destNotReached = true;

    map.set(start, Cell::Start);

    for (; destNotReached && !wave.empty(); destNotReached = (map.get(destination) == Cell::Unused)) {

        for (Point pos: wave) {
            map.forEachNeighbor(pos, [&] (Point neighbor) {
                if (map.get(neighbor) == Cell::Unused) {
                    nextWave.insert(neighbor);
                }
                return true;
            });
        }

        Cell next = current.next();
        for (Point pos: nextWave) {
            map.set(pos, next);
        }
        std::swap(current, next);
        wave = std::exchange(nextWave, {});
    }
    return !destNotReached;
}

std::vector<Point> backtrace(const Map& map, Point start, Point destination) {
    std::vector<Point> trace = {destination};

    Point back = trace.back();

    while (back != start) {
        Cell currentCell = map.get(back);

        map.forEachNeighbor(back, [&] (Point neighbor) {
            const Cell neighborCell = map.get(neighbor);
            Cell next = neighborCell.next();

            if (next == currentCell) {
                trace.push_back(neighbor);
                back = neighbor;
                return false;
            }
            return true;
        });
    }
    return trace;
}

std::vector<Point> shortestPath(Map map, Point start, Point destination) {
    if (waveExpansion(map, start, destination)) {
        return backtrace(map, start, destination);
    }
    return {};
}

int main() {
    auto [map, start, dest] = fromString("        \n"
                                         "        \n"
                                         "  DXXX  \n"
                                         "  XX X  \n"
                                         "  X     \n"
                                         "  X S   \n"
                                         "        \n"
                                         "        \n");
    const std::vector<Point> path = shortestPath(map, start, dest);

    //hack for show path
    for (Point p: path) {
        map.set(p, Cell::Marker::Start);
    }
    print(map, start, dest);
}
