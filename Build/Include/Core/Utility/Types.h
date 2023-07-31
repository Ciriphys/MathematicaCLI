#pragma once

// Forward declarations
struct RationalNumber;

// Data structures
using String = std::string;
using StringStream = std::stringstream;
using Any = std::any;

template<typename T>
using Vector = std::vector<T>;

template<typename T, size_t S>
using Array = std::array<T, S>;

template<typename K, typename V>
using HashMap = std::unordered_map<K, V>;

template<typename K, typename V>
using Map = std::map<K, V>;

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
using UInt64  = unsigned long long int;
using UInt32  = unsigned int;
using UInt16  = unsigned short;
using UInt8   = unsigned char;
using Int64   = long long int;
using Int32   = int;
using Int16	  = short;
using Int8	  = char;
using Float32 = float;
using Float64 = double;

// Smart pointers
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T>
using Scope = std::unique_ptr<T>;