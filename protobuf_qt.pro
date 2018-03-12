TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
        include \
        compiler \
        tests

tests.depends = compiler
