#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <utility>

#include "view.h"

namespace homework5 {
    enum class Operation: std::uint_least16_t;

    class ViewCLI: public View {
    public:
        ViewCLI() :  _primitivesAvailable{false}, _controller {nullptr}, _model{nullptr} {}

        ViewCLI(const ViewCLI&) = delete;
        ViewCLI& operator=(const ViewCLI&) = delete;

        ViewCLI(ViewCLI&&) = delete;
        ViewCLI& operator=(ViewCLI&&) = delete;

        ~ViewCLI() override = default;

        int start(DocumentModel* model, Controller* controler) override;

    protected:
        int _init(DocumentModel* model, Controller* controller);
        int _showDocState();

        bool _isOpAvailable(Operation operation);

        bool _primitivesAvailable;

        Controller* _controller;
        DocumentModel* _model;

        std::map<Operation, std::pair<std::string, std::function<int()> > > _dispatcher;
    };
}