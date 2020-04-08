#pragma once

#include <vector>
#include <memory>

template<typename T>
using vector = std::vector<T>;

template<typename T>
using shared_ptr = std::shared_ptr<T>;

template<typename T>
using unique_ptr = std::unique_ptr<T>;
