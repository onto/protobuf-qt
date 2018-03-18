#include "insertion_point_writer.h"

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/compiler/code_generator.h>

InsertionPointWriter::InsertionPointWriter(google::protobuf::compiler::GeneratorContext *generator_context,
        const std::string &filename, const std::string &insertion_point)
    : _stream(generator_context->OpenForInsert(filename, insertion_point))
    , _printer(std::make_unique<google::protobuf::io::Printer>(_stream.get(), '$'))
{
}

InsertionPointWriter::~InsertionPointWriter() = default;
InsertionPointWriter::InsertionPointWriter(InsertionPointWriter &&) = default;
InsertionPointWriter &InsertionPointWriter::operator=(InsertionPointWriter &&) = default;

void InsertionPointWriter::write(const char *str)
{
    _printer->Print(str);
}

void InsertionPointWriter::write(const char *str, const std::map<std::string, std::string> &params)
{
    _printer->Print(params, str);
}

void InsertionPointWriter::writeln(const char *str)
{
    _printer->Print(str);
    _printer->Print("\n");
}

void InsertionPointWriter::writeln(const char *str, const std::map<std::string, std::string> &params)
{
    _printer->Print(params, str);
    _printer->Print("\n");
}

void InsertionPointWriter::indent()
{
    _printer->Indent();
}

void InsertionPointWriter::outdent()
{
    _printer->Outdent();
}

InsertionPointWriterFactory::InsertionPointWriterFactory(const std::string &filename,
        google::protobuf::compiler::GeneratorContext *generator_context)
    : _generator_context(generator_context)
{
    auto filename_without_proto = filename.substr(0, filename.size() - strlen("proto"));
    _header = filename_without_proto + "pb.h";
    _source = filename_without_proto + "pb.cc";
}

InsertionPointWriter InsertionPointWriterFactory::make_header_writer(const std::string &insertion_point)
{
    return InsertionPointWriter(_generator_context, _header, insertion_point);
}

InsertionPointWriter InsertionPointWriterFactory::make_source_writer(const std::string &insertion_point)
{
    return InsertionPointWriter(_generator_context, _source, insertion_point);
}

