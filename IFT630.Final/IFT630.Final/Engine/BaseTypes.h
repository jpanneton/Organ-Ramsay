#pragma once

#include <cstdint>

using Bool = bool;

using Int8 = int8_t;
using Int16 = int16_t;
using Int32 = int32_t;
using Int64 = int64_t;

using UInt8 = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt64 = uint64_t;

using Float32 = float;
using Float64 = double;

#if _WIN64
using Int = Int64;
using Float = Float64;
#else
using Int = Int32;
using Float = Float32;
#endif