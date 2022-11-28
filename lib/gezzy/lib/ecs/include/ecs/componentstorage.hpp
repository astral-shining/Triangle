#pragma once
#include <cpputils/fastvector.hpp>
#include <tuple>

template<typename... Ts>
struct ComponentStorage {
    std::tuple<FastVector<Ts>...> storage;
};