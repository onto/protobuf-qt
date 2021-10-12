#ifndef INSERTION_POINT_WRITER_H
#define INSERTION_POINT_WRITER_H

#include <memory>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

namespace google
{
    namespace protobuf
    {
        namespace compiler
        {
            class GeneratorContext;
        }
        namespace io
        {
            class ZeroCopyOutputStream;
            class Printer;
        }
    }
}

class InsertionPointWriter
{
public:
    InsertionPointWriter(google::protobuf::compiler::GeneratorContext *generator_context,
                         const std::string &filename,
                         const std::string &insertion_point);

    ~InsertionPointWriter();
    InsertionPointWriter(InsertionPointWriter &&);
    InsertionPointWriter &operator=(InsertionPointWriter &&);

    void write(const char *str);
    void write(const char *str, const std::map<std::string, std::string> &params);
    void writeln(const char *str);
    void writeln(const char *str, const std::map<std::string, std::string> &params);

    void indent();
    void outdent();

private:
    std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream> _stream;
    std::unique_ptr<google::protobuf::io::Printer> _printer;
};

class InsertionPointWriterFactory
{
public:
    InsertionPointWriterFactory(const std::string &filename,
                                google::protobuf::compiler::GeneratorContext *generator_context);

    InsertionPointWriter make_header_writer(const std::string &insertion_point);
    InsertionPointWriter make_source_writer(const std::string &insertion_point);

private:
    google::protobuf::compiler::GeneratorContext *_generator_context;

    std::string _header;
    std::string _source;
};

#endif // INSERTION_POINT_WRITER_H
