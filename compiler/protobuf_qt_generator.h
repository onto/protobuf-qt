#ifndef PROTOBUF_QT_GENERATOR_H
#define PROTOBUF_QT_GENERATOR_H

#include <google/protobuf/compiler/code_generator.h>

class InsertionPointWriterFactory;

class ProtobufQtGenerator : public google::protobuf::compiler::CodeGenerator
{
public:
    ProtobufQtGenerator() = default;

    bool Generate(const google::protobuf::FileDescriptor *file,
                  const std::string &parameter,
                  google::protobuf::compiler::GeneratorContext *generator_context,
                  std::string *error) const override;

    void Generate(const google::protobuf::FileDescriptor &file,
                  InsertionPointWriterFactory &writer_factory) const;
};

#endif // PROTOBUF_QT_GENERATOR_H
