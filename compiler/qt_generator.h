#ifndef QT_GENERATOR_H
#define QT_GENERATOR_H

#include <google/protobuf/compiler/plugin.pb.h>

namespace google
{
namespace protobuf
{
namespace compiler
{
namespace qt
{
    CodeGeneratorResponse generate(const CodeGeneratorRequest &request);
}
}
}
}

#endif // QT_GENERATOR_H
