#include "protobuf_qt_generator.h"

#include <google/protobuf/compiler/plugin.h>

#include <iostream>

int main(int argc, char **argv)
{
    ProtobufQtGenerator generator;
    return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}

