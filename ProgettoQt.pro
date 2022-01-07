TEMPLATE = app

TARGET = ProgettoQt

QT = core gui widgets charts

QMAKE_CXXFLAGS += -Wno-deprecated-copy

HEADERS += \
    chartview.h \
    controller.h \
    dialogs.h \
    graph.h \
    labels.h \
    model.h \
    table.h \
    view.h

SOURCES += \
    chartview.cpp \
    controller.cpp \
    dialogs.cpp \
    graph.cpp \
    labels.cpp \
    main.cpp \
    model.cpp \
    table.cpp \
    view.cpp

RESOURCES += \
    resources.qrc
