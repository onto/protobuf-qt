# Protobuf-Qt

This lib should help with usage of generated sources from Google Protobuf files with Qt and QML.

## Idea
Just write plugin for current C++ generator:

+ Add getter/setter for std::string as QString
+ Mark all messages classes as QObject
+ Add Q_PROPERTY for all messages fields
    - Wrap repeated fields by QQmlListProperty
    - Add signals for fields changes

## Usage
+ Build compiler
+ Generate sources; example command:
```sh
    protoc --plugin=protoc-gen-qt=protoc-gen-qt --cpp_out=. --qt_out=. Test.proto
```
+ Profit

## List of known insertion points (look at orignal C++ generator)

`$full_name$` mean:

+ `package.ClassName` for message type
+ `package.ClassName.field_name` for field

### File (google/protobuf/compiler/cpp/cpp_file.cc)
+ includes
+ namespace_scope
+ global_scope

### Message type (google/protobuf/compiler/cpp/cpp_message.cc)
+ class_definition:$full_name$
+ dep_base_class_definition:$full_name$
+ class_scope:$full_name$
+ constructor:$full_name$
+ arena_constructor:$full_name$
+ copy_constructor:$full_name$
+ destructor:$full_name$
+ message_clear_start:$full_name$
+ one_of_clear_start:$full_name$
+ generalized_merge_from_start:$full_name$
+ generalized_merge_from_cast_fail:$full_name$
+ generalized_merge_from_cast_success:$full_name$
+ class_specific_merge_from_start:$full_name$
+ generalized_copy_from_start:$full_name$
+ class_specific_copy_from_start:$full_name$
+ parse_start:$full_name$
+ parse_success:$full_name$
+ parse_failure:$full_name$
+ serialize_start:$full_name$
+ serialize_end:$full_name$
+ serialize_to_array_start:$full_name$
+ serialize_to_array_end:$full_name$
+ message_set_byte_size_start:$full_name$
+ required_fields_byte_size_fallback_start:$full_name$
+ message_byte_size_start:$full_name$

### Primitive field (google/protobuf/compiler/cpp/cpp_primitive_field.cc)
+ field_get:$full_name$
+ field_set:$full_name$

### Primitive repeated field (google/protobuf/compiler/cpp/cpp_primitive_field.cc)
+ field_get:$full_name$
+ field_set:$full_name$
+ field_add:$full_name$
+ field_list:$full_name$
+ field_mutable_list:$full_name$

### String field (google/protobuf/compiler/cpp/cpp_string_field.cc)
+ field_get:$full_name$
+ field_set:$full_name$
+ field_set_rvalue:$full_name$
+ field_set_char:$full_name$
+ field_set_pointer:$full_name$
+ field_mutable:$full_name$
+ field_release:$full_name$
+ field_set_allocated:$full_name$
+ field_unsafe_arena_release:$full_name$
+ field_unsafe_arena_set_allocated:$full_name$

### String repeated field (google/protobuf/compiler/cpp/cpp_string_field.cc)
+ field_get:$full_name$
+ field_set:$full_name$
+ field_set_rvalue:$full_name$
+ field_set_char:$full_name$
+ field_set_pointer:$full_name$
+ field_mutable:$full_name$
+ field_add_mutable:$full_name$
+ field_add:$full_name$
+ field_add_char:$full_name$
+ field_add_pointer:$full_name$
+ field_list:$full_name$
+ field_mutable_list:$full_name$

### Enum field (google/protobuf/compiler/cpp/cpp_enum_field.cc)
+ field_get:$full_name$
+ field_set:$full_name$

### Enum repeated field (google/protobuf/compiler/cpp/cpp_enum_field.cc)
+ field_get:$full_name$
+ field_set:$full_name$
+ field_add:$full_name$
+ field_list:$full_name$
+ field_mutable_list:$full_name$

### Map field (google/protobuf/compiler/cpp/cpp_map_field.cc)
+ field_map:$full_name$
+ field_mutable_map:$full_name$

### Message field (google/protobuf/compiler/cpp/cpp_message_field.cc)
+ field_unsafe_arena_set_allocated:$full_name$
+ field_get:$full_name$
+ field_release:$full_name$
+ field_unsafe_arena_release:$full_name$
+ field_mutable:$full_name$
+ field_set_allocated:$full_name$

### Message repeated field (google/protobuf/compiler/cpp/cpp_message_field.cc)
+ field_add:$full_name$
+ field_mutable:$full_name$
+ field_get:$full_name$
+ field_list:$full_name$