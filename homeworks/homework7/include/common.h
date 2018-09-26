#pragma once

#include <memory>
#include <string>
#include <vector>

namespace homework7{

    using bulk_t = std::vector<std::string>;

    class Observer {
    public:
        virtual void update(const bulk_t&) = 0;
    };

    class Subject {
    public:
        void attach(std::unique_ptr<Observer> observer) {
            _observers.emplace_back(std::move(observer)); //.emplace_back(std::move(observer));
        }
    protected:
        virtual void _notify() = 0;

        std::vector<std::unique_ptr<Observer> > _observers;
    };


}