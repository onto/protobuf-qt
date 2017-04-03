#ifndef GOOGLE_PROTOBUF_COMPILER_QT_OPTIONS_H__
#define GOOGLE_PROTOBUF_COMPILER_QT_OPTIONS_H__

#include <string>

#include <google/protobuf/stubs/common.h>
namespace google {
namespace protobuf {
namespace compiler {
namespace qt {

// Generator options (see generator.cc for a description of each):
struct Options {
  Options()
      : safe_boundary_check(false),
        proto_h(false),
        allow_import_public(true),
        annotate_headers(false),
        enforce_lite(false) {}

  string dllexport_decl;
  bool safe_boundary_check;
  bool proto_h;
  bool allow_import_public;
  bool annotate_headers;
  bool enforce_lite;
  string annotation_pragma_name;
  string annotation_guard_name;
};

}  // namespace qt
}  // namespace compiler
}  // namespace protobuf


}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_QT_OPTIONS_H__
