#include "test_messages_proto3.pb.h"

#include <QtGlobal>

int main(int /*argc*/, char */*argv*/[])
{
    protobuf_test_messages::proto3::TestAllTypes m1;
    Q_UNUSED(m1);
    protobuf_test_messages::proto3::ForeignMessage m2;
    Q_UNUSED(m2);
    protobuf_test_messages::proto3::ForeignEnum e1;
    Q_UNUSED(e1);
}
