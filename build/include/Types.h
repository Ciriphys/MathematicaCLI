#pragma once

#include <memory>
#include <vector>
#include <string>

// Type definitions
template<typename T>
using MVector = std::vector<T>;
using MString = std::string;

template<typename T>
using MRef = std::shared_ptr<T>;

template<typename T>
using MScoped = std::unique_ptr<T>;