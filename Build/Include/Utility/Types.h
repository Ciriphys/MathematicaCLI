#pragma once

#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

// Data structures
template<typename T>
using MVector = std::vector<T>;
template<typename K, typename V>
using MHashMap = std::unordered_map<K, V>;
using MString = std::string;
using MStringStream = std::stringstream;

// Smart pointers
template<typename T>
using MRef = std::shared_ptr<T>;
template<typename T>
using MScoped = std::unique_ptr<T>;