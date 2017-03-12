#ifndef GOOGLE_PROTOBUF_QT_GENERATED_MESSAGE_UTIL_H__
#define GOOGLE_PROTOBUF_QT_GENERATED_MESSAGE_UTIL_H__

#include <QString>

namespace google {
namespace protobuf {
namespace internal {

inline const QString& GetEmptyQStringAlreadyInited() {
  const static QString fixed_address_empty_string = QStringLiteral("");
  return fixed_address_empty_string;
}

inline const QString& GetEmptyQString() {
  return GetEmptyQStringAlreadyInited();
}

inline int QStringSpaceUsedExcludingSelf(const QString& str) {
    return str.capacity();
}

} // namespace google
} // namespace protobuf
} // namespace internal

#endif // GOOGLE_PROTOBUF_QT_GENERATED_MESSAGE_UTIL_H__
