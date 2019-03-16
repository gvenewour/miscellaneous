#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include <experimental/filesystem>

#include "geometry.h"

namespace homework5 {

    namespace fs = std::experimental::filesystem;

    class DocumentModel {
    public:
        int importFromFile(const fs::path& path);
        int exportToFile(const fs::path& path);

        template<typename T, typename... Args>
        int addPrimitive(Args&&... args) {
            _primitives.emplace_back(std::make_unique<T>(args...));
        }

        const Primitives& getPrimitives() const {
            return _primitives;
        }

        void removeLastAdded();
        void removeAll();

    protected:
        Primitives _primitives;
    };
}
