#include "qt_generator.h"

#include <iostream>

int main(int /*argc*/, char */*argv*/[])
{
    google::protobuf::compiler::CodeGeneratorRequest request;
    return (request.ParseFromIstream(&std::cin)
            && google::protobuf::compiler::qt::generate(request).SerializeToOstream(&std::cout)) ? 0 : -1;
}
