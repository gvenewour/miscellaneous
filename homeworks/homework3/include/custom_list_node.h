#pragma once

namespace homework3 {
    namespace impl {
        template<typename T>
        struct Node {
            T val;
            Node *next{nullptr};
        };
    }
}