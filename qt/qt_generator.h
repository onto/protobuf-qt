#ifndef QTPROTOBUFGENERATOR_H
#define QTPROTOBUFGENERATOR_H

#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace qt {

class QtProtobufGenerator : public google::protobuf::compiler::CodeGenerator
{
public:
    virtual bool Generate(const google::protobuf::FileDescriptor *file,
                          const std::string &parameter,
                          google::protobuf::compiler::GeneratorContext *generator_context,
                          std::string *error) const override;
};

}
}
}
}

#endif // QTPROTOBUFGENERATOR_H
