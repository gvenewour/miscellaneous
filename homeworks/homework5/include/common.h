#pragma once

//#include <cstdint>

namespace homework5 {
    class Observer {
    public:
        virtual void update(bool optionsAvailable) = 0;
    };

}

