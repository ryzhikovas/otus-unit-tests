#pragma once
#include <string>
#include <tuple>
#include "../Map.hpp"

void print(const Map& m, Point start, Point destination);
std::tuple<Map, Point, Point> fromString(const std::string& s);