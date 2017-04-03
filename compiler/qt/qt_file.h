#ifndef GOOGLE_PROTOBUF_COMPILER_QT_FILE_H__
#define GOOGLE_PROTOBUF_COMPILER_QT_FILE_H__

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <string>
#include <vector>
#include <google/protobuf/stubs/common.h>

#include "qt_field.h"
#include "qt_options.h"

namespace google {
namespace protobuf {
  class FileDescriptor;        // descriptor.h
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace qt {

class EnumGenerator;           // enum.h
class MessageGenerator;        // message.h
class ServiceGenerator;        // service.h
class ExtensionGenerator;      // extension.h

class FileGenerator {
 public:
  // See generator.cc for the meaning of dllexport_decl.
  FileGenerator(const FileDescriptor* file, const Options& options);
  ~FileGenerator();

  // Shared code between the two header generators below.
  void GenerateHeader(io::Printer* printer);

  // info_path, if non-empty, should be the path (relative to printer's output)
  // to the metadata file describing this proto header.
  void GenerateProtoHeader(io::Printer* printer,
                           const string& info_path);
  // info_path, if non-empty, should be the path (relative to printer's output)
  // to the metadata file describing this PB header.
  void GeneratePBHeader(io::Printer* printer,
                        const string& info_path);
  void GenerateSource(io::Printer* printer);

 private:
  // Internal type used by GenerateForwardDeclarations (defined in file.cc).
  class ForwardDeclarations;

  // Generate the BuildDescriptors() procedure, which builds all descriptors
  // for types defined in the file.
  void GenerateBuildDescriptors(io::Printer* printer);

  void GenerateNamespaceOpeners(io::Printer* printer);
  void GenerateNamespaceClosers(io::Printer* printer);

  // For other imports, generates their forward-declarations.
  void GenerateForwardDeclarations(io::Printer* printer);

  // Internal helper used by GenerateForwardDeclarations: fills 'decls'
  // with all necessary forward-declarations for this file and its
  // transient depednencies.
  void FillForwardDeclarations(ForwardDeclarations* decls);

  // Generates top or bottom of a header file.
  void GenerateTopHeaderGuard(io::Printer* printer,
                              const string& filename_identifier);
  void GenerateBottomHeaderGuard(io::Printer* printer,
                                 const string& filename_identifier);

  // Generates #include directives.
  void GenerateLibraryIncludes(io::Printer* printer);
  void GenerateDependencyIncludes(io::Printer* printer);

  // Generate a pragma to pull in metadata using the given info_path (if
  // non-empty). info_path should be relative to printer's output.
  void GenerateMetadataPragma(io::Printer* printer, const string& info_path);

  // Generates a couple of different pieces before definitions:
  void GenerateGlobalStateFunctionDeclarations(io::Printer* printer);

  // Generates types for classes.
  void GenerateMessageDefinitions(io::Printer* printer);

  void GenerateEnumDefinitions(io::Printer* printer);

  // Generates generic service definitions.
  void GenerateServiceDefinitions(io::Printer* printer);

  // Generates extension identifiers.
  void GenerateExtensionIdentifiers(io::Printer* printer);

  // Generates inline function defintions.
  void GenerateInlineFunctionDefinitions(io::Printer* printer);

  void GenerateProto2NamespaceEnumSpecializations(io::Printer* printer);

  const FileDescriptor* file_;
  const Options options_;

  // Contains the post-order walk of all the messages (and child messages) in
  // this file. If you need a pre-order walk just reverse iterate.
  std::vector<MessageGenerator*> message_generators_;
  std::vector<EnumGenerator*> enum_generators_;
  std::vector<ServiceGenerator*> service_generators_;
  std::vector<ExtensionGenerator*> extension_generators_;

  // These members are just for owning (and thus proper deleting). Some of the
  // message_ and enum_generators above are owned by child messages.
  google::protobuf::scoped_array<google::protobuf::scoped_ptr<MessageGenerator> >
      message_generators_owner_;
  google::protobuf::scoped_array<google::protobuf::scoped_ptr<EnumGenerator> > enum_generators_owner_;
  google::protobuf::scoped_array<google::protobuf::scoped_ptr<ServiceGenerator> >
      service_generators_owner_;
  google::protobuf::scoped_array<google::protobuf::scoped_ptr<ExtensionGenerator> >
      extension_generators_owner_;

  // E.g. if the package is foo.bar, package_parts_ is {"foo", "bar"}.
  std::vector<string> package_parts_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileGenerator);
};

}  // namespace qt
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_QT_FILE_H__
