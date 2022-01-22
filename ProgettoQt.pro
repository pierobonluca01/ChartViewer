TEMPLATE = app

TARGET = ProgettoQt

QT = core gui widgets charts

QMAKE_CXXFLAGS += -Wno-deprecated-copy

HEADERS += \
    chart.h \
    controller.h \
    dialogs.h \
    graph.h \
    labels.h \
    model.h \
    table.h \
    view.h

SOURCES += \
    chart.cpp \
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
