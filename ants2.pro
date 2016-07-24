QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE *= -O3

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ants2
TEMPLATE = app


SOURCES += main.cpp \
    colonie.cpp \
    instance.cpp \
    cview.cpp \
    interface.cpp

HEADERS += \
    instance.h \
    colonie.h \
    cview.h \
    interface.h
