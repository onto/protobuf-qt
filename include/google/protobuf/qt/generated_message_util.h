#ifndef GOOGLE_PROTOBUF_QT_GENERATED_MESSAGE_UTIL_H__
#define GOOGLE_PROTOBUF_QT_GENERATED_MESSAGE_UTIL_H__

class QString;

namespace google {
namespace protobuf {
namespace internal {

const QString& GetEmptyQStringAlreadyInited();

inline const QString& GetEmptyQString() {
  return GetEmptyQStringAlreadyInited();
}

int QStringSpaceUsedExcludingSelf(const QString& str);

} // namespace google
} // namespace protobuf
} // namespace internal

#endif // GOOGLE_PROTOBUF_QT_GENERATED_MESSAGE_UTIL_H__
