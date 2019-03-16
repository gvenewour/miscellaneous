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

    void ViewCLI::start() {

        uint16_t tmp{0};
        Operation request {Operation::maxOp};
        int result {0};

        do {
            _showDocState();

            std::cout << "\nPrint action number: " << "\n";

            for (const auto& operation: _dispatcher) {
                if (_isOpAvailable(operation.first)) {
                    std::cout << static_cast<uint16_t>(operation.first) << " - " << operation.second.first << "\n";
                }
            }

            std::cout << "0 - Exit" << "\n\n";
            std::cout <<"> Chosen action: ";
            std::cin >> tmp;

            if (!std::cin.good()) {
                std::cout << ">> Invalid operation requested, terminating program" << "\n";
                return;
            }

            if (tmp < MaxOp) {
                if (tmp == 0) {
                    return;
                }
                request = static_cast<Operation>(tmp);

                if (_isOpAvailable(request)) {
                    result = _dispatcher[request].second();
                    std::cout << ">> " << (result == OK? "Operation was finished successfully" : "Operation failed") << "\n";
                } else {
                    std::cout << ">> Please choose a valid option from the list" << "\n";
                }
            } else {
                std::cout << ">> Please choose a valid option from the list" << "\n";
            }

            std::cout << "\n";
        } while (true);
    }

    bool ViewCLI::_isOpAvailable(homework5::Operation operation) {
        return (operation != Operation::removeLastAdded || _primitivesAvailable);
    }

    void ViewCLI::setModel(DocumentModel *model) {
        _model = model;
    }

    void ViewCLI::setController(Controller *controller) {
        _controller = controller;

        _dispatcher[Operation::create] = std::make_pair("Create new document",
                                                        [this](){ return _controller->createDoc();});
        _dispatcher[Operation::import] = std::make_pair("Import new document from file",
                                                        [this](){ return _controller->importDoc();});
        _dispatcher[Operation::exportFrom] = std::make_pair("Export the current document to file",
                                                            [this](){return _controller->exportDoc();});
        _dispatcher[Operation::addLine] = std::make_pair("Add a new line", [this](){return _controller->addLine();});
        _dispatcher[Operation::addPoint] = std::make_pair("Add a new point", [this](){return _controller->addPoint();});
        _dispatcher[Operation::removeLastAdded] = std::make_pair("Remove the last added primitive",
                                                            [this](){return _controller->removeLastAdded();});
    }

    void ViewCLI::_showDocState() {
        decltype(auto) geometry = _model->getPrimitives();
        _primitivesAvailable = !geometry.empty();

        std::cout << "Current document: ";

        if (!_primitivesAvailable) {
            std::cout << "no primitives available" << "\n";
            return;
        }

        std::cout << geometry.size() << " primitives (" ;

        for (decltype(geometry.size()) i = 0; i < geometry.size(); ++i)
            std::cout << "type: " << *geometry[i] << (i < geometry.size() - 1 ? ", " : "");

        std::cout << ")\n";
    }


}