#include "qt_file.h"

#include "qt_message.h"

namespace google
{
namespace protobuf
{
namespace compiler
{
namespace qt
{

void generate_file(const FileDescriptorProto &file, CodeGeneratorResponse &response)
{
    // remove proto, add pb.h
    auto filename_without_proto = file.name().substr(0, file.name().size() - 5);

    auto generated_header = filename_without_proto + "pb.h";
    auto generated_source = filename_without_proto + "pb.cc";

    auto *result_file = response.add_file();
    result_file->set_name(generated_header);
    result_file->set_insertion_point("includes");
    result_file->set_content("#include <QObject>");

    for (auto &message : file.message_type())
    {
        generate_message_header(message, generated_header, response);
        generate_message_source(message, generated_source, response);
    }
}

}
}
}
}
