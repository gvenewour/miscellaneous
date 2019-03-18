#pragma once

namespace homework5 {
    class Controller;
    class DocumentModel;

    class View {
    public:
        virtual int start(DocumentModel *model, Controller *controler) = 0;

        virtual ~View() = default;
    };
}