#pragma once

#include <cstdint>
#include <memory>
#include <iostream>
#include <string>

#include "storage.h"

namespace homework7 {
    class Parser {
    public:
        explicit Parser(uint64_t chunksMaxDefault);
        void start();

    private:
        enum State {
            DEFAULT, BLOCK
        };

        bool _isReserved(const std::string& token) {
            return (token == _blockStart) || (token == _blockEnd);
        }

        void _manageReserved(const std::string& token);
        void _manageRegular(std::string&& token);

        void _finalize();

        uint64_t _chunksMaxDefault;
        uint64_t _chunkIndex;

        uint64_t _blockLevel;

        std::unique_ptr<Storage> _storage;

        State _state;

        const std::string _blockStart;
        const std::string _blockEnd;
    };

}