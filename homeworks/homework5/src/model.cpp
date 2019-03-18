#include "model.h"

namespace homework5 {
    int DocumentModel::importFromFile(const fs::path& path){
        //NOTE: implement if needed
        return Error::OK;
    }

    int DocumentModel::exportToFile(const fs::path& path) {
        //NOTE: implement if needed
        return Error::OK;
    }

    int DocumentModel::removeLastAdded() {
        if (!_primitives.empty())
            _primitives.pop_back();

        return Error::OK;
    }

    int DocumentModel::removeAll() {
        _primitives.clear();

        return Error::OK;
    }
}