#include "controller.h"

namespace homework5 {

Controller::Controller() {
    _view.setController(this);
    _view.setModel(&_model);

    _model.registerObserver(&_view);
}

void Controller::createDoc() {
    _model.removeAll();
}

void Controller::importDoc() {
    importDoc("default.txt");
}

void Controller::importDoc(const std::string& name) {
    //FIXME!
}

void Controller::exportDoc() {
    exportDoc("default.txt");
}

void Controller::exportDoc(const std::string& name) {
    //FIXME!
}

void Controller::addLine() {
    //TODO: add random coordinates
    addLine(0, 0, 100, 200);
}

void Controller::addLine(Point start, Point end) {
    _model.addPrimitive<Line>(start, end);
}

void Controller::addLine(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2) {
    _model.addPrimitive<Line>(x1, y1, x2, y2);
}

void Controller::addPoint() {
    //TODO: add random coordinates
    _model.addPrimitive<Point>(0, 0);
}

void Controller::removeLastAdded() {
    _model.removeLastAdded();
}
}