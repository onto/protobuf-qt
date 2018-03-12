TEMPLATE = app
CONFIG += console c++11
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
    qt_generator.cpp \
    qt_file.cpp \
    qt_message.cpp

HEADERS += \
    qt_generator.h \
    qt_file.h \
    qt_message.h
