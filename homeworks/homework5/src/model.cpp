#include "model.h"

namespace homework5 {
    int DocumentModel::importFromFile(const fs::path& path){
        //NOTE: implement if needed
    }

    int DocumentModel::exportToFile(const fs::path& path) {
        //NOTE: implement if needed
    }

    void DocumentModel::removeLastAdded() {
        if (!_primitives.empty())
            _primitives.pop_back();
    }

    void DocumentModel::removeAll() {
        _primitives.clear();
    }
}