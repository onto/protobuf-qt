#ifndef REPEATED_FIELDS_H
#define REPEATED_FIELDS_H

#include "repeated_field_adaptor.h"

#include <google/protobuf/descriptor.h>

inline auto repeated_message_adaptor(const google::protobuf::FileDescriptor &file_descriptor)
{
    return repeated_adaptor(file_descriptor,
                            &google::protobuf::FileDescriptor::message_type_count,
                            &google::protobuf::FileDescriptor::message_type);
}

inline auto repeated_enum_adaptor(const google::protobuf::FileDescriptor &file_descriptor)
{
    return repeated_adaptor(file_descriptor,
                            &google::protobuf::FileDescriptor::enum_type_count,
                            &google::protobuf::FileDescriptor::enum_type);
}

inline auto repeated_enum_value_adaptor(const google::protobuf::EnumDescriptor &enum_descriptor)
{
    return repeated_adaptor(enum_descriptor,
                            &google::protobuf::EnumDescriptor::value_count,
                            &google::protobuf::EnumDescriptor::value);
}

inline auto repeated_field_adaptor(const google::protobuf::Descriptor &message_descriptor)
{
    return repeated_adaptor(message_descriptor,
                            &google::protobuf::Descriptor::field_count,
                            &google::protobuf::Descriptor::field);
}

inline auto repeated_oneof_adaptor(const google::protobuf::Descriptor &message_descriptor)
{
    return repeated_adaptor(message_descriptor,
                            &google::protobuf::Descriptor::oneof_decl_count,
                            &google::protobuf::Descriptor::oneof_decl);
}

inline auto repeated_nested_type_adaptor(const google::protobuf::Descriptor &message_descriptor)
{
    return repeated_adaptor(message_descriptor,
                            &google::protobuf::Descriptor::nested_type_count,
                            &google::protobuf::Descriptor::nested_type);
}

inline auto repeated_enum_adaptor(const google::protobuf::Descriptor &message_descriptor)
{
    return repeated_adaptor(message_descriptor,
                            &google::protobuf::Descriptor::enum_type_count,
                            &google::protobuf::Descriptor::enum_type);
}

inline auto repeated_field_adaptor(const google::protobuf::OneofDescriptor &oneof_descriptor)
{
    return repeated_adaptor(oneof_descriptor,
                            &google::protobuf::OneofDescriptor::field_count,
                            &google::protobuf::OneofDescriptor::field);
}

#endif // REPEATED_FIELDS_H
