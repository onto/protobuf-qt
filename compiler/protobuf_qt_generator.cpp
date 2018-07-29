#include "protobuf_qt_generator.h"

#include "insertion_point_writer.h"
#include "repeated_fields.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

#include <regex>
#include <algorithm>

namespace
{
    std::string dot_to_colon(const std::string &str)
    {
        const static std::regex regex(R"(\.)");
        return std::regex_replace(str, regex, "::");
    }

    std::string snake_to_camel(const std::string &str)
    {
        std::string result;
        result.reserve(str.size());

        bool uppercase_next = false;
        for (char c : str)
        {
            if (c == '_')
            {
                uppercase_next = true;
            }
            else
            {
                result += uppercase_next ? static_cast<char>(std::toupper(static_cast<int>(c))) : c;
                uppercase_next = false;
            }
        }

        return result;
    }

    std::string to_lowercase(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](char c)
        {
            return static_cast<char>(std::tolower(static_cast<int>(c)));
        });
        return str;
    }

    std::string cpp_type(const google::protobuf::Descriptor &message_descriptor)
    {
        return dot_to_colon(message_descriptor.full_name());
    }

    std::string cpp_type(const google::protobuf::EnumDescriptor &enum_descriptor)
    {
        return dot_to_colon(enum_descriptor.full_name());
    }

    std::string cpp_type(const google::protobuf::FieldDescriptor &field_descriptor)
    {
        google::protobuf::FieldDescriptor::CppType type = field_descriptor.cpp_type();
        switch (type)
        {
        case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
            return "qint32";
        case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
            return "qint64";
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
            return "quint32";
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
            return "quint64";
        case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
            return "qreal";
        case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
            return "qreal";
        case google::protobuf::FieldDescriptor::CPPTYPE_ENUM:
            return cpp_type(*field_descriptor.enum_type());
        case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
            return "QString";
        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
            return cpp_type(*field_descriptor.message_type());
        case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
            return "bool";
        }

        throw std::runtime_error("cpp_type: invalid field type");
    }

    std::string cpp_wrapper_type(const google::protobuf::EnumDescriptor &enum_descriptor)
    {
        if (enum_descriptor.containing_type()) // enum in message
        {
            return cpp_type(*enum_descriptor.containing_type()) + "Wrapper::" + enum_descriptor.name();
        }
        else // global enum
        {
            return cpp_type(enum_descriptor) + "Wrapper::" + enum_descriptor.name();
        }
    }

    void generate_global_enum_declaration(InsertionPointWriter &writer,
                                          const google::protobuf::EnumDescriptor &enum_descriptor)
    {
        writer.write(
            "class $enum_name$Wrapper {\n"
            "  Q_GADGET\n"
            "public:\n"
            "  enum $enum_name$ {\n",
        {
            { "enum_name", enum_descriptor.name() }
        });

        for (const google::protobuf::EnumValueDescriptor &enum_value : repeated_enum_value_adaptor(enum_descriptor))
        {
            writer.write(
                "    $enum_value$ = $source_enum_name$::$enum_value$,\n",
            {
                { "source_enum_name", cpp_type(enum_descriptor) },
                { "enum_value", enum_value.name() }
            });
        }

        writer.write(
            "  };\n"
            "  Q_ENUM($enum_name$)\n"
            "};\n"
            "\n",
        {
            { "enum_name", enum_descriptor.name() }
        });
    }

    void generate_enum_declaration(InsertionPointWriter &writer,
                                   const google::protobuf::EnumDescriptor &enum_descriptor)
    {
        writer.write(
            "  enum $enum_name$ {\n",
        {
            { "enum_name", enum_descriptor.name() }
        });

        for (const google::protobuf::EnumValueDescriptor &enum_value : repeated_enum_value_adaptor(enum_descriptor))
        {
            writer.write(
                "    $enum_value$ = $source_enum_name$::$enum_value$,\n",
            {
                { "source_enum_name", cpp_type(*enum_descriptor.containing_type()) },
                { "enum_value", enum_value.name() }
            });
        }

        writer.write(
            "  };\n"
            "  Q_ENUM($enum_name$)\n"
            "\n",
        {
            { "enum_name", enum_descriptor.name() }
        });
    }

    void generate_property_declaration(InsertionPointWriter &writer,
                                       const google::protobuf::FieldDescriptor &field)
    {
        if (field.is_map())
        {

        }
        else if (field.is_repeated())
        {

        }
        else
        {
            std::map<std::string, std::string> params =
            {
                { "field_name", snake_to_camel(field.lowercase_name()) },
                { "setter_name", snake_to_camel("set_" + field.lowercase_name()) }
            };

            if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)
            {
                params["field_type"] = field.message_type()->name() + "Wrapper *";
                return;
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)
            {
                params["field_type"] = cpp_wrapper_type(*field.enum_type());
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
            {
                if (field.options().has_ctype())
                {
                    return;
                }

                params["field_type"] = "QString";
            }
            else
            {
                params["field_type"] = cpp_type(field);
            }

            writer.write("  Q_PROPERTY($field_type$ $field_name$ READ $field_name$ "
                         "WRITE $setter_name$ NOTIFY $field_name$Changed)\n", params);
        }
    }

    void generate_signal_declaration(InsertionPointWriter &writer,
                                     const google::protobuf::FieldDescriptor &field)
    {
        if (field.is_map())
        {

        }
        else if (field.is_repeated())
        {

        }
        else
        {
            std::map<std::string, std::string> params =
            {
                { "field_name", snake_to_camel(field.lowercase_name()) },
            };

            if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)
            {
                params["field_type"] = field.message_type()->name() + "Wrapper *";
                return;
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)
            {
                params["field_type"] = cpp_wrapper_type(*field.enum_type());
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
            {
                if (field.options().has_ctype())
                {
                    return;
                }

                params["field_type"] = "QString";
            }
            else
            {
                params["field_type"] = cpp_type(field);
            }

            writer.write("  void $field_name$Changed($field_type$ value);\n", params);
        }
    }

    void generate_setter_getter_declaration(InsertionPointWriter &writer,
                                            const google::protobuf::FieldDescriptor &field)
    {
        if (field.is_map())
        {

        }
        else if (field.is_repeated())
        {

        }
        else
        {
            std::map<std::string, std::string> params =
            {
                { "field_name", snake_to_camel(field.lowercase_name()) },
                { "setter_name", snake_to_camel("set_" + field.lowercase_name()) }
            };

            if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)
            {
                params["field_type"] = field.message_type()->name() + "Wrapper *";
                return;
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)
            {
                params["field_type"] = cpp_wrapper_type(*field.enum_type());
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
            {
                if (field.options().has_ctype())
                {
                    return;
                }

                params["field_type"] = "QString";
            }
            else
            {
                params["field_type"] = cpp_type(field);
            }

            writer.write(
                "  $field_type$ $field_name$() const;\n"
                "  void $setter_name$($field_type$ value);\n",
                params);
        }
    }

    void generate_setter_getter_implementation(InsertionPointWriter &writer,
            const google::protobuf::FieldDescriptor &field,
            const std::string &class_name)
    {
        if (field.is_map())
        {

        }
        else if (field.is_repeated())
        {

        }
        else
        {
            std::map<std::string, std::string> params =
            {
                { "field_name", snake_to_camel(field.lowercase_name()) },
                { "setter_name", snake_to_camel("set_" + field.lowercase_name()) },
                { "class_name", class_name },
                { "source_class_name", dot_to_colon(field.containing_type()->full_name()) },
                { "source_field_name", to_lowercase(field.name()) },
            };

            if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE)
            {
                params["field_type"] = field.message_type()->name() + "Wrapper *";
                return;
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM)
            {
                params["field_type"] = cpp_wrapper_type(*field.enum_type());
                params["original_enum_type"] = dot_to_colon(field.enum_type()->full_name());

                writer.write(
                    "  $field_type$ $class_name$Wrapper::$field_name$() const {\n"
                    "    return static_cast<$field_type$>($source_class_name$::$source_field_name$());\n"
                    "  }\n"
                    "\n"
                    "  void $class_name$Wrapper::$setter_name$($field_type$ value) {\n"
                    "    $source_class_name$::set_$source_field_name$(static_cast<$original_enum_type$>(value));\n"
                    "  }\n"
                    "\n"
                    , params);
            }
            else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING)
            {                
                if (field.options().has_ctype())
                {
                    return;
                }

                writer.write(
                    "  QString $class_name$Wrapper::$field_name$() const {\n"
                    "    return QString::fromStdString($source_class_name$::$source_field_name$());\n"
                    "  }\n"
                    "\n"
                    "  void $class_name$Wrapper::$setter_name$(QString value) {\n"
                    "    $source_class_name$::set_$source_field_name$(value.toStdString());\n"
                    "  }\n"
                    "\n"
                    , params);
            }
            else
            {
                params["field_type"] = cpp_type(field);

                writer.write(
                    "  $field_type$ $class_name$Wrapper::$field_name$() const {\n"
                    "    return $source_class_name$::$source_field_name$();\n"
                    "  }\n"
                    "\n"
                    "  void $class_name$Wrapper::$setter_name$($field_type$ value) {\n"
                    "    $source_class_name$::set_$source_field_name$(value);\n"
                    "  }\n"
                    "\n"
                    , params);
            }
        }
    }

    void generate_nested_typedef_declaration(InsertionPointWriter &writer,
            const google::protobuf::Descriptor &descriptor,
            const std::string &parent_class = "")
    {
        if (descriptor.options().map_entry())
        {
            return;
        }

        const std::string class_name = parent_class.empty()
                                       ? descriptor.name()
                                       : parent_class + "_" + descriptor.name();

        writer.write(
            " typedef $full_class_name$Wrapper $class_name$Wrapper;\n",
        {
            { "full_class_name", class_name },
            { "class_name", descriptor.name() }
        });
    }

    void generate_message_declaration(InsertionPointWriter &writer,
                                      const google::protobuf::Descriptor &descriptor,
                                      const std::string &parent_class = "")
    {
        if (descriptor.options().map_entry())
        {
            return;
        }

        const std::string class_name = parent_class.empty()
                                       ? descriptor.name()
                                       : parent_class + "_" + descriptor.name();

        for (const google::protobuf::Descriptor &nested_descriptor : repeated_nested_type_adaptor(descriptor))
        {
            generate_message_declaration(writer, nested_descriptor, class_name);
        }

        writer.write(
            "class $class_name$Wrapper : public QObject, public $class_name$ {\n"
            "  Q_OBJECT\n"
            ,
        {
            { "class_name", class_name }
        });

        writer.write(
            "\n"
            "public:\n"
        );

        for (const google::protobuf::EnumDescriptor &enum_descriptor : repeated_enum_adaptor(descriptor))
        {
            generate_enum_declaration(writer, enum_descriptor);
        }

        writer.write(
            "private:\n"
        );

        for (const google::protobuf::FieldDescriptor &field : repeated_field_adaptor(descriptor))
        {
            generate_property_declaration(writer, field);
        }

        writer.write(
            "\n"
            "public:\n"
        );

        for (const google::protobuf::Descriptor &nested_descriptor : repeated_nested_type_adaptor(descriptor))
        {
            generate_nested_typedef_declaration(writer, nested_descriptor, class_name);
        }

        writer.write(
            "\n"
            "signals:\n"
        );

        for (const google::protobuf::FieldDescriptor &field : repeated_field_adaptor(descriptor))
        {
            generate_signal_declaration(writer, field);
        }

        writer.write(
            "\n"
            "public:\n"
        );

        for (const google::protobuf::FieldDescriptor &field : repeated_field_adaptor(descriptor))
        {
            generate_setter_getter_declaration(writer, field);
        }

        writer.write(
            "};\n"
            "\n",
        {
        });
    }

    void generate_message_implementation(InsertionPointWriter &writer,
                                         const google::protobuf::Descriptor &descriptor,
                                         const std::string &parent_class = "")
    {
        if (descriptor.options().map_entry())
        {
            return;
        }

        const std::string class_name = parent_class.empty()
                                       ? descriptor.name()
                                       : parent_class + "_" + descriptor.name();

        for (const google::protobuf::Descriptor &nested_descriptor : repeated_nested_type_adaptor(descriptor))
        {
            generate_message_implementation(writer, nested_descriptor, class_name);
        }

        for (const google::protobuf::FieldDescriptor &field : repeated_field_adaptor(descriptor))
        {
            generate_setter_getter_implementation(writer, field, class_name);
        }
    }

    void generate_forward_declaration(InsertionPointWriter &writer,
                                      const google::protobuf::Descriptor &descriptor,
                                      const std::string &parent_class = "")
    {
        if (descriptor.options().map_entry())
        {
            return;
        }

        const std::string class_name = parent_class.empty()
                                       ? descriptor.name()
                                       : parent_class + "_" + descriptor.name();

        writer.write("class $class_name$Wrapper;\n", {{"class_name", class_name}});

        for (const google::protobuf::Descriptor &nested_descriptor : repeated_nested_type_adaptor(descriptor))
        {
            generate_forward_declaration(writer, nested_descriptor, class_name);
        }
    }


}

bool ProtobufQtGenerator::Generate(const google::protobuf::FileDescriptor *file,
                                   const std::string &/*parameter*/,
                                   google::protobuf::compiler::GeneratorContext *generator_context,
                                   std::string *error) const
{
    try
    {
        InsertionPointWriterFactory writer_factory(file->name(), generator_context);
        Generate(*file, writer_factory);
    }
    catch (const std::exception &ex)
    {
        *error = ex.what();
        return false;
    }

    return true;
}

void ProtobufQtGenerator::Generate(const google::protobuf::FileDescriptor &file,
                                   InsertionPointWriterFactory &writer_factory) const
{
    {
        auto writer = writer_factory.make_header_writer("includes");
        writer.writeln("#include <QObject>");
    }

    auto header_writer = writer_factory.make_header_writer("namespace_scope");
    auto source_writer = writer_factory.make_source_writer("namespace_scope");

    for (const google::protobuf::Descriptor &descriptor : repeated_message_adaptor(file))
    {
        generate_forward_declaration(header_writer, descriptor);
    }

    header_writer.write("\n");

    for (const google::protobuf::EnumDescriptor &global_enum : repeated_enum_adaptor(file))
    {
        generate_global_enum_declaration(header_writer, global_enum);
    }

    for (const google::protobuf::Descriptor &descriptor : repeated_message_adaptor(file))
    {
        generate_message_declaration(header_writer, descriptor);
        generate_message_implementation(source_writer, descriptor);
    }
}
