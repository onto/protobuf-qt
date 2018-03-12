#ifndef QT_FILE_H
#define QT_FILE_H

#include <google/protobuf/compiler/plugin.pb.h>

namespace google
{
namespace protobuf
{
namespace compiler
{
namespace qt
{
    void generate_file(const FileDescriptorProto &file, CodeGeneratorResponse &response);
}
}
}
}

#endif // QT_FILE_H
