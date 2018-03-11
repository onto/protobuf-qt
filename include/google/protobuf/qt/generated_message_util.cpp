#include "generated_message_util.h"

#include <QString>

namespace google {
namespace protobuf {
namespace internal {

const QString& GetEmptyQStringAlreadyInited() {
    const static QString fixed_address_empty_string = QStringLiteral("");
    return fixed_address_empty_string;
}

int QStringSpaceUsedExcludingSelf(const QString &str) {
    return str.capacity();
}

} // namespace google
} // namespace protobuf
} // namespace internal

