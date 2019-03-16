#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <utility>

namespace homework5 {
    enum class Operation: std::uint_least16_t;
    class Controller;
    class DocumentModel;

    class View {
    public:
        virtual void start() = 0;
        virtual ~View() = default;
    };

    class ViewCLI: public View {
    public:
        ViewCLI() :  _primitivesAvailable{false}, _controller {nullptr}, _model{nullptr} {}

        ViewCLI(const ViewCLI&) = delete;
        ViewCLI& operator=(const ViewCLI&) = delete;

        ViewCLI(ViewCLI&&) = delete;
        ViewCLI& operator=(ViewCLI&&) = delete;

        ~ViewCLI() override = default;

        void start() override;

        void setModel(DocumentModel* model);
        void setController(Controller* controller);

    protected:
        void _showDocState();

        bool _isOpAvailable(Operation operation);

        bool _primitivesAvailable;

        Controller* _controller;
        DocumentModel* _model;

        std::map<Operation, std::pair<std::string, std::function<int()> > > _dispatcher;
    };
}