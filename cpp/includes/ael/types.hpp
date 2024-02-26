#ifndef AEL_TYPES_H_
#define AEL_TYPES_H_

#include <cmath>
#include <cstdint>

namespace ael::types {

// Unsigned
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;

// Signed
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;

// floating point numbers
using f32 = std::float_t;
using f64 = std::double_t;

}  // namespace ael
#endif  // ! AEL_TYPES_H_
