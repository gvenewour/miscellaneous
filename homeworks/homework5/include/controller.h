#pragma once

#include "geometry.h"
#include "model.h"
#include "view_cli.h"

namespace homework5 {
    class Controller {
    public:
        Controller() = default;
        Controller(const Controller&) = delete;
        Controller& operator=(const Controller&) = delete;

        Controller(Controller&&) = delete;
        Controller& operator=(Controller&&) = delete;

        ~Controller() = default;

        int startUI();

        int createDoc();
        int importDoc();
        int importDoc(const std::string& name);

        int exportDoc();
        int exportDoc(const std::string& name);

        int addLine();
        int addLine(Point start, Point end);
        int addLine(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2);

        int addPoint();

        int removeLastAdded();

    private:
        ViewCLI _view;
        DocumentModel _model;
    };
}