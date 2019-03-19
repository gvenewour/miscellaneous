#include "controller.h"

namespace homework5 {

//Controller::Controller() {
//    _view.setController(this);
//    _view.setModel(&_model);

//    _model.registerObserver(&_view);
//}

int Controller::startUI() {
    return _view.start(&_model, this);
}

int Controller::createDoc() {
    return _model.removeAll();
}

int Controller::importDoc() {
    return importDoc("default.txt");
}

int Controller::importDoc(const std::string& name) {
    return _model.importFromFile(name);
}

int Controller::exportDoc() {
    return exportDoc("default.txt");
}

int Controller::exportDoc(const std::string& name) {
    return _model.exportToFile(name);
}

int Controller::addLine() {
    //NOTE: add random coordinates if necessary
    return addLine(0, 0, 100, 200);
}

int Controller::addLine(Point start, Point end) {
    return _model.addPrimitive<Line>(start, end);
}

int Controller::addLine(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2) {
    return _model.addPrimitive<Line>(x1, y1, x2, y2);
}

int Controller::addPoint() {
    //NOTE: add random coordinates if necessary
    return _model.addPrimitive<Point>(0, 0);
}

int Controller::removeLastAdded() {
    return _model.removeLastAdded();
}
}