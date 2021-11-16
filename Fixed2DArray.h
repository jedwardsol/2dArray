#pragma once

#include <array>

template <typename T, size_t ROWS, size_t COLUMNS>
using FixedTwoDArray = std::array< std::array<T,COLUMNS>, ROWS>;
