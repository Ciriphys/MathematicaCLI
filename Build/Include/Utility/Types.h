#pragma once

// Forward declarations
struct MNumber;

// Data structures
template<typename T>
using MVector = std::vector<T>;
template<typename K, typename V>
using MHashMap = std::unordered_map<K, V>;
using MString = std::string;
using MStringStream = std::stringstream;
template<typename T>
using MStack = std::stack<T>;
template<typename F, typename S>
using MPair = std::pair<F, S>;
using MAny = std::any;

// Miscellaneous
using MMersenneTwister = std::mt19937;
using MRandomDevice = std::random_device;

// Functions
typedef MNumber(*FBinaryFunction)(const MNumber&, const MNumber&);

// Primitive types
using uint64 = unsigned long long int;
using uint32 = unsigned int;
using int64  = long long int;
using int32  = int;

// Smart pointers
template<typename T>
using MRef = std::shared_ptr<T>;
template<typename T>
using MScope = std::unique_ptr<T>;