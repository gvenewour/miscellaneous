#include <iostream>

#include <cstdint>
#include "view.h"
#include "model.h"
#include "controller.h"

namespace homework5 {
    enum class Operation: std::uint_least16_t {
        create = 1,
        import,
        //show,
        exportFrom,
        addPoint,
        addLine,
        removeLastAdded,
        maxOp
    };
    constexpr const auto MaxOp {static_cast<uint_least16_t>(Operation::maxOp)};

    void ViewCLI::update(bool primitivesAvailable) {
        _primitivesAvailable = primitivesAvailable;
    }

    void ViewCLI::start() {
        uint16_t tmp{0};

        do {
            _showDocState();

            std::cout << "Print action number: " << "\n";

            for (auto& operation: _dispatcher) {
                if (operation.first != Operation::removeLastAdded || _primitivesAvailable) {
                    std::cout << static_cast<uint16_t>(operation.first) << " - " << operation.second.first << "\n";
                }
            }

            std::cout << "0 - Exit" << "\n";
            std::cin >> tmp;

            if (!std::cin.good()) {
                std::cout << "Invalid operation requested, terminating program" << "\n";
                return;
            }

            if (tmp < MaxOp) {
                if (tmp == 0) {
                    return;
                }
                auto operation = static_cast<Operation>(tmp);
                _dispatcher[operation].second();
            } else {
                std::cout << "Please choose a valid option from the list" << "\n";
            }
        } while (true);
    }

    void ViewCLI::setModel(DocumentModel *model) {
        _model = model;
    }

    void ViewCLI::setController(Controller *controller) {
        _controller = controller;

        _dispatcher[Operation::create] = std::make_pair("Create new document",
                                                        [this](){ _controller->createDoc();});
        _dispatcher[Operation::import] = std::make_pair("Import new document from file",
                                                        [this](){ _controller->importDoc();});
//        _dispatcher[Operation::show] = std::make_pair("Show current document content",
//                                                      [this]() {_controller->show();});
        _dispatcher[Operation::exportFrom] = std::make_pair("Export the current document to file",
                                                            [this](){_controller->exportDoc();});
        _dispatcher[Operation::addLine] = std::make_pair("Add a new line", [this](){_controller->addLine();});
        _dispatcher[Operation::addPoint] = std::make_pair("Add a new point", [this](){_controller->addPoint();});
        _dispatcher[Operation::removeLastAdded] = std::make_pair("Remove the last added primitive",
                                                            [this](){_controller->removeLastAdded();});
    }

    void ViewCLI::_showDocState() {
        decltype(auto) geometry = _model->getPrimitives();

        std::cout << "Current document: ";

        if (geometry.empty()) {
            std::cout << "no primitives available" << "\n";
            return;
        }

        std::cout << geometry.size() << " primitives (" ;

        for(const auto& primitive: geometry) {
            std::cout << "type: " << *primitive << " ";
        }

        std::cout << ")\n";
    }


}