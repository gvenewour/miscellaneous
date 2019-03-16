#include "model.h"

namespace homework5 {
    void DocumentModel::removeLastAdded() {
        _primitives.pop_back();

        if (_primitives.empty()) {
            _notifyObservers();
        }
    }

    void DocumentModel::removeAll() {
        _primitives.clear();
        _notifyObservers();
    }

    void DocumentModel::removeObserver(Observer *observer) {
        _observers.erase(std::remove_if(_observers.begin(), _observers.end(),
                                        [observer](Observer* element) {
                                            return (element == observer);
                                        }),
                         _observers.end());
    }
}