#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include <experimental/filesystem>

#include "geometry.h"

namespace homework5 {

    namespace fs = std::experimental::filesystem;

    constexpr const auto OK = 0;

    class DocumentModel {
    public:
        int importFromFile(const fs::path& path);
        int exportToFile(const fs::path& path);

        template<typename T, typename... Args>
        int addPrimitive(Args&&... args) {
            _primitives.emplace_back(std::make_unique<T>(args...));

            return OK;
        }

        const Primitives& getPrimitives() const {
            return _primitives;
        }

        int removeLastAdded();
        int removeAll();

    protected:
        Primitives _primitives;
    };
}
