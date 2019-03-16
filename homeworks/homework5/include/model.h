#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "common.h"
#include "geometry.h"

namespace homework5 {

    class DocumentModel {
    public:
//        int importFromFile() {
//
//        }
//
//        int exportToFile() {
//
//        }

        template<typename T, typename... Args>
        int addPrimitive(Args&&... args) {
            bool updateUIRequired = _primitives.empty();

            _primitives.emplace_back(std::make_unique<T>(args...));
            if (updateUIRequired) {
                _notifyObservers();
            }
        }

        const Primitives& getPrimitives() const {
            return _primitives;
        }

        void removeLastAdded();
        void removeAll();

        void registerObserver(Observer* observer) {
            _observers.push_back(observer);
        }

        void removeObserver(Observer* observer);

    protected:
        void _notifyObservers() {
            for (const auto& element: _observers) {
                element->update(!_primitives.empty());
            }
        }

        Primitives _primitives;
        std::vector<Observer*> _observers;
    };
}
