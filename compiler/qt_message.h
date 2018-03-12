#ifndef QT_MESSAGE_H
#define QT_MESSAGE_H

#include <google/protobuf/compiler/plugin.pb.h>

namespace google
{
namespace protobuf
{
namespace compiler
{
namespace qt
{

    void generate_message_header(const DescriptorProto &message,
                                 const std::string &filename,
                                 CodeGeneratorResponse &response);

    void generate_message_source(const DescriptorProto &message,
                                 const std::string &filename,
                                 CodeGeneratorResponse &response);

}
}
}
}

#endif // QT_MESSAGE_H
