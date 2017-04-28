#include "generated_message_util.h"

#include <QString>

const QString &google::protobuf::internal::GetEmptyQStringAlreadyInited() {
    const static QString fixed_address_empty_string = QStringLiteral("");
    return fixed_address_empty_string;
}

int google::protobuf::internal::QStringSpaceUsedExcludingSelf(const QString &str) {
    return str.capacity();
}
