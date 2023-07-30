#pragma once

// Forward declarations
struct RationalNumber;

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

// Files
using OutFile = std::ofstream;
using InFile = std::ifstream;
using File = std::fstream;

// Chrono
template<typename D>
using TimePoint = std::chrono::time_point<D>;

using SteadyClock = std::chrono::steady_clock;

using Nanoseconds  = std::chrono::nanoseconds;
using Milliseconds = std::chrono::milliseconds;
using Microseconds = std::chrono::microseconds;

// Miscellaneous
using MersenneTwister = std::mt19937;
using RandomDevice = std::random_device;

// Functions
typedef RationalNumber(*FBinaryFunction)(const RationalNumber&, const RationalNumber&);

// Primitive types
using uint64  = unsigned long long int;
using uint32  = unsigned int;
using uint16  = unsigned short;
using uint8   = unsigned char;
using int64   = long long int;
using int32   = int;
using int16	  = short;
using int8	  = char;
using float32 = float;
using float64 = double;

// Smart pointers
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T>
using Scope = std::unique_ptr<T>;