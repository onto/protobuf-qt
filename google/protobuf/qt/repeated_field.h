#ifndef GOOGLE_PROTOBUF_QT_REPEATED_FIELD_H__
#define GOOGLE_PROTOBUF_QT_REPEATED_FIELD_H__

#include <QString>

#include <google/protobuf/repeated_field.h>
#include <google/protobuf/arena.h>

#include "generated_message_util.h"

namespace google {
namespace protobuf {
namespace internal {

class QStringTypeHandler {
 public:
  typedef QString Type;

  static inline QString* New(Arena* arena) {
    return Arena::Create<QString>(arena);
  }
  static inline QString* NewFromPrototype(const QString*,
                                         ::google::protobuf::Arena* arena) {
    return New(arena);
  }
  static inline ::google::protobuf::Arena* GetArena(QString*) {
    return NULL;
  }
  static inline void* GetMaybeArenaPointer(QString* /* value */) {
    return NULL;
  }
  static inline void Delete(QString* value, Arena* arena) {
    if (arena == NULL) {
      delete value;
    }
  }
  static inline void Clear(QString* value) { value->clear(); }
  static inline void Merge(const QString& from, QString* to) { *to = from; }
  static inline const Type& default_instance() {
    return GetEmptyQString();
  }
  static int SpaceUsed(const QString& value)  {
    return static_cast<int>(sizeof(value)) + QStringSpaceUsedExcludingSelf(value);
  }
};

} // namespace internal

template <>
class RepeatedPtrField<QString>::TypeHandler
    : public internal::QStringTypeHandler {
};

} // namespace protobuf
} // namespace google

#endif // GOOGLE_PROTOBUF_QT_REPEATED_FIELD_H__
