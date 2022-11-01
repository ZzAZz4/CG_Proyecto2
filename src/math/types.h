

#ifndef OGL_TYPES_H
#define OGL_TYPES_H

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using uptr = uintptr_t;
using sptr = intptr_t;
using usize = size_t;
using ssize = ssize_t;


typedef glm::tvec4<u8> byte4;

#endif //OGL_TYPES_H
