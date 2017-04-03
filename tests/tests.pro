TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

TARGET=protobuf_qt_test

INCLUDEPATH += $${PROTOBUF_SRC}
INCLUDEPATH += ../include

LIBS += -L$${PROTOBUF_LIBS}
LIBS += -lprotobuf

SOURCES += main_test.cpp

PROTOS = Test.proto

PROTOC = $${PROTOBUF_LIBS}/protoc.sh
PROTOC_GEN_QT=../compiler/protoc-gen-qt.sh

protobuf_decl.name = protobuf headers
protobuf_decl.input = PROTOS
protobuf_decl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.pb.h
protobuf_decl.commands = $${PROTOC} --plugin=protoc-gen-qt=$${PROTOC_GEN_QT} --qt_out=${QMAKE_FILE_IN_PATH} -I=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_IN}
protobuf_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_decl

protobuf_impl.name = protobuf sources
protobuf_impl.input = PROTOS
protobuf_impl.output = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.pb.cc
protobuf_impl.depends = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_BASE}.pb.h
protobuf_impl.commands = $$escape_expand(\n)
protobuf_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_impl

