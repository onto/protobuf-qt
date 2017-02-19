#include <google/protobuf/compiler/plugin.h>

#include "qt/qt_generator.h"

int main(int argc, char *argv[])
{
    google::protobuf::compiler::qt::QtProtobufGenerator generator;
    return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}
