#include "parser.h"

namespace homework7 {

    Parser::Parser(uint64_t chunksMaxDefault)  : _chunksMaxDefault{chunksMaxDefault},
                                                 _chunkIndex{0},
                                                 _blockLevel{0},
                                                 _storage{std::make_unique<SimpleStorage>()},
                                                 _state{State::DEFAULT},
                                                 _blockStart{"{"},
                                                 _blockEnd{"}"}
    {
        _storage->attach(std::make_unique<ConsoleLogger>());
        _storage->attach(std::make_unique<FileLogger>());
    }

    void Parser::start() {
        std::string token{}, skip{};

        std::istream &stream = std::cin;
        while ((stream >> token)) {
            if (_isReserved(token)) {
                _manageReserved(token);
            } else {
                _manageRegular(std::move(token));
            }
            std::getline(stream, skip);
        }
        _finalize();
    }

    void Parser::_manageReserved(const std::string& token) {
        if (token == _blockStart) {
            if (_state == State::DEFAULT) {
                _storage->apply();
                _chunkIndex = 0;
                _state = State::BLOCK;
            } else {
                ++_blockLevel;
            }
        } else {    //token == _blockEnd
            if (_state == State::BLOCK) {
                if (_blockLevel == 0) {
                    _storage->apply();
                    _state = State::DEFAULT;
                } else {
                    --_blockLevel;
                }
            }
        }
    }

    void Parser::_manageRegular(std::string&& token) {
        _storage->stash(std::move(token));
        if ((_state == DEFAULT) && (++_chunkIndex == _chunksMaxDefault)) {
            _storage->apply();
            _chunkIndex = 0;
        }
    }

    void Parser::_finalize() {
        if (_state == DEFAULT) {
            _storage->apply();
        }
    }
}