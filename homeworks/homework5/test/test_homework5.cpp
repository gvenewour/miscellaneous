#include "gtest/gtest.h"

#include <string>
#include "controller.h"

using namespace homework5;

TEST(Homework5, ModelDefault) {
    DocumentModel model;

    decltype(auto) geometry = model.getPrimitives();
    ASSERT_EQ(geometry.size(), 0);  //more general than empty()

    ASSERT_EQ(model.removeLastAdded(), Error::OK);
    ASSERT_EQ(model.removeAll(), Error::OK);
}

TEST(Homework5, ModelDataManipulation) {
    DocumentModel model;

    decltype(auto) geometry = model.getPrimitives();

    model.addPrimitive<Point>(0, 0);
    ASSERT_EQ(geometry.size(), 1);
    ASSERT_EQ((*geometry.cbegin())->type(), GeometryType::Point);

    model.addPrimitive<Point>(100, 100);

    model.addPrimitive<Line>(0, 0, 100, 100);
    ASSERT_EQ(geometry.size(), 3);
    ASSERT_EQ((*geometry.crbegin())->type(), GeometryType::Line);

    ASSERT_EQ(model.removeLastAdded(), Error::OK);
    ASSERT_EQ(geometry.size(), 2);

    ASSERT_EQ(model.removeAll(), Error::OK);
    ASSERT_TRUE(geometry.empty());
}

TEST(Homework5, ModelFileStub) {
    constexpr auto defaultPath {"default.txt"};
    DocumentModel model;

    ASSERT_EQ(model.importFromFile(defaultPath), Error::OK);

    //TODO: fill the example file and add more tests if file manipulation is required

    ASSERT_EQ(model.exportToFile(defaultPath), Error::OK);
}

TEST(Homework5, ViewDefault) {
    ViewCLI view;
    ASSERT_EQ(view.start(0, 0), NOT_INITIALIZED);
    ASSERT_EQ(view.start(nullptr, nullptr), NOT_INITIALIZED);
}

TEST(Homework5, ControllerInterface) {
    Controller controller;
    ASSERT_EQ(controller.createDoc(), Error::OK);
    ASSERT_EQ(controller.importDoc(), Error::OK);
    ASSERT_EQ(controller.exportDoc(), Error::OK);

    //TODO: if file manipulation is required, add tests for import and export functions

    ASSERT_EQ(controller.removeLastAdded(), Error::OK);
    ASSERT_EQ(controller.addLine(), Error::OK);
    ASSERT_EQ(controller.addPoint(), Error::OK);
    ASSERT_EQ(controller.removeLastAdded(), Error::OK);
    ASSERT_EQ(controller.createDoc(), Error::OK);

    //TODO: add other tests if extended implementation is required
}