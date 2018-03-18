TEMPLATE = app
CONFIG += console c++11 c++14 c++17 c++1z
CONFIG -= app_bundle
CONFIG -= qt

TARGET = protoc-gen-qt

win32:INCLUDEPATH += $${PROTOBUF_SRC}
win32:LIBS += -L$${PROTOBUF_LIBS}

CONFIG(debug, debug|release) {
    unix:LIBS += -lprotobuf -lprotoc
    win32:LIBS += -llibprotobufd -llibprotocd
} else {
    unix:LIBS += -lprotobuf -lprotoc
    win32:LIBS += -llibprotobuf -llibprotoc
}

SOURCES += main.cpp \
    protobuf_qt_generator.cpp \
    insertion_point_writer.cpp

HEADERS += \
    protobuf_qt_generator.h \
    insertion_point_writer.h
