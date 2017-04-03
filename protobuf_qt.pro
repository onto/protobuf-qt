TEMPLATE = subdirs
CONFIG += ordered

isEmpty(PROTOBUF_SRC) {
error("Need to define PROTOBUF_SRC")
}

isEmpty(PROTOBUF_LIBS) {
error("Need to define PROTOBUF_LIBS")
}

SUBDIRS = \
        include \
        compiler \
        tests

tests.depends = compiler
