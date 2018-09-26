#pragma once

#include <iostream>
#include "common.h"

namespace homework7 {

//    class Logger: public Observer {
//    public:
//        explicit Logger(Subject *model)
//        {
//            model->attach(this);
//        }
//    };

    class ConsoleLogger: public Observer {
    public:
        void update(const bulk_t& bulk) override {
            std::cout << "bulk: ";
            for (const auto& el: bulk) {
                std::cout << el << " ";
            }
            std::cout << "\n";
        }
    };

    class FileLogger: public Observer {
    public:
        void update(const bulk_t& bulk) override {
            //TODO: FILESYSTEM
        }
    };
}

