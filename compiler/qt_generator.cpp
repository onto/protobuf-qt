#include "qt_generator.h"

#include "qt_file.h"

#include <fstream>

namespace google
{
namespace protobuf
{
namespace compiler
{
namespace qt
{

CodeGeneratorResponse generate(const CodeGeneratorRequest &request)
{
    CodeGeneratorResponse result;

    std::set<std::string> file_to_generate(request.file_to_generate().begin(),
                                           request.file_to_generate().end());

    for (auto &file : request.proto_file())
    {
        if (file_to_generate.count(file.name()) == 0)
            continue;

        generate_file(file, result);
    }

    return result;
}

}
}
}
}

