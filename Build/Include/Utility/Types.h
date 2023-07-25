#pragma once

// Forward declarations
struct Number;

// Data structures
using String = std::string;
using StringStream = std::stringstream;
using Any = std::any;

template<typename T>
using Vector = std::vector<T>;

template<typename K, typename V>
using HashMap = std::unordered_map<K, V>;

template<typename K, typename V>
using Map = std::map<K, V>;

template<typename T>
using Stack = std::stack<T>;

template<typename F, typename S>
using Pair = std::pair<F, S>;

// Miscellaneous
using MersenneTwister = std::mt19937;
using RandomDevice = std::random_device;

// Functions
typedef Number(*FBinaryFunction)(const Number&, const Number&);

// Primitive types
using uint64  = unsigned long long int;
using uint32  = unsigned int;
using int64   = long long int;
using int32   = int;
using float32 = float;
using float64 = double;

// Smart pointers
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T>
using Scope = std::unique_ptr<T>;