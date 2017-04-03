TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = protoc-gen-qt

INCLUDEPATH += $${PROTOBUF_SRC}
LIBS += -L$${PROTOBUF_LIBS}
LIBS += -lprotobuf -lprotoc

SOURCES += main.cpp \
    qt/qt_generator.cpp \
    qt/qt_helpers.cpp \
    qt/qt_file.cpp \
    qt/qt_field.cpp \
    qt/qt_enum.cpp \
    qt/qt_service.cpp \
    qt/qt_extension.cpp \
    qt/qt_message.cpp \
    qt/qt_primitive_field.cpp \
    qt/qt_string_field.cpp \
    qt/qt_enum_field.cpp \
    qt/qt_message_field.cpp \
    qt/qt_map_field.cpp

HEADERS += \
    qt/qt_generator.h \
    qt/qt_options.h \
    qt/qt_helpers.h \
    qt/qt_file.h \
    qt/qt_field.h \
    qt/qt_enum.h \
    qt/qt_service.h \
    qt/qt_extension.h \
    qt/qt_message.h \
    qt/qt_primitive_field.h \
    qt/qt_string_field.h \
    qt/qt_enum_field.h \
    qt/qt_message_field.h \
    qt/qt_map_field.h
