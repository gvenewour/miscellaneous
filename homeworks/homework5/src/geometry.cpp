#include "geometry.h"

namespace homework5 {
    std::ostream& operator<<(std::ostream& os, const GeometricPrimitive& pr) {
        os << static_cast<uint_least32_t>(pr.type());
        return os;
    }
}