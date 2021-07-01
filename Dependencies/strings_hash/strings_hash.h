#include <cstdint>
#include <stdint.h>

namespace detail{
    constexpr std::uint32_t fnv1a_32(char const* s, size_t count){
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
    }
}   

constexpr std::uint32_t operator""_h(char const* s, size_t count){return detail::fnv1a_32(s, count);}
