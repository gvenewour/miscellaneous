#include <cstddef>

constexpr size_t bin_id(size_t x, bool inRecurse = false) {
        return (x < 2 )                          ?  0 :
               (inRecurse || ((x & (x-1)) == 0)) ?  
               1 + bin_id(x >> 1, inRecurse) :
               2 + bin_id(x >> 1, true);
}
