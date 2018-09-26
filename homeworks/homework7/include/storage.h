#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "common.h"
#include "logger.h"

namespace homework7 {
    class Storage: public Subject {
    public:
        virtual void stash(std::string&& token) = 0;
        virtual void apply() = 0;
    };

    class SimpleStorage: public Storage {
    public:

        void stash(std::string&& token) override {
            if (_bulk.empty()) {
                //TODO: save timestamp
            }

            _bulk.emplace_back(std::move(token));
        }

        void apply() override {
            if (!_bulk.empty()) {
                _notify();
                _bulk.clear();
            }
        }

    private:
        void _notify() override {
            for (auto& logger: _observers) {
                logger->update(_bulk);
            }
        }

        bulk_t _bulk;
    };
}