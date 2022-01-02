TEMPLATE = app

TARGET = ProgettoQt

QT = core gui widgets

QMAKE_CXXFLAGS += -Wno-deprecated-copy

HEADERS += \
    controller.h \
    graph.h \
    labels.h \
    model.h \
    table.h \
    view.h

SOURCES += \
    controller.cpp \
    graph.cpp \
    labels.cpp \
    main.cpp \
    model.cpp \
    table.cpp \
    view.cpp

RESOURCES += \
    resources.qrc
