#pragma once

#include "geometry.h"
#include "model.h"
#include "view.h"

namespace homework5 {
    class Controller {
    public:
        Controller();

        void startUI() {
            _view.start();
        }

        void createDoc();
        void importDoc();
        void importDoc(const std::string& name);

        void exportDoc();
        void exportDoc(const std::string& name);

        void addLine();
        void addLine(Point start, Point end);
        void addLine(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2);

        void addPoint();

        void removeLastAdded();

    private:
        ViewCLI _view;
        DocumentModel _model;
    };
}