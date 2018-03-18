#include "protobuf_qt_generator.h"

#include "insertion_point_writer.h"

#include <google/protobuf/descriptor.h>

bool ProtobufQtGenerator::Generate(const google::protobuf::FileDescriptor *file,
                                   const std::string &/*parameter*/,
                                   google::protobuf::compiler::GeneratorContext *generator_context,
                                   std::string *error) const
{
    try
    {
        InsertionPointWriterFactory writer_factory(file->name(), generator_context);
        Generate(*file, writer_factory);
    }
    catch (const std::exception &ex)
    {
        *error = ex.what();
        return false;
    }

    return true;
}

void ProtobufQtGenerator::Generate(const google::protobuf::FileDescriptor &file,
                                   InsertionPointWriterFactory &writer_factory) const
{
    auto writer = writer_factory.make_header_writer("includes");
    writer.writeln("/* Hello from Protobuf-Qt plugin! */");
    writer.writeln("/* Write for file $file$ */", {{"file", file.name()}});
}
