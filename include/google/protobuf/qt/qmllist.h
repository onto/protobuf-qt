#ifndef GOOGLE_PROTOBUF_QT_QML_QMLLIST_H__
#define GOOGLE_PROTOBUF_QT_QML_QMLLIST_H__

#include <QQmlListProperty>

#include <google/protobuf/repeated_field.h>

namespace google {
namespace protobuf {
namespace qt {
namespace qml {

template<typename T>
void append_function_primitive(QQmlListProperty<T> *property, T *value)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedField<T>*>(property->data);
  repeated_field->Add(*value);
}

template<typename T>
void append_function_object(QQmlListProperty<T> *property, T *value)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedPtrField<T>*>(property->data);
  repeated_field->AddAllocated(value);
}

template<typename T>
T *at_function_primitive(QQmlListProperty<T> *property, int index)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedField<T>*>(property->data);
  return repeated_field->Mutable(index);
}

template<typename T>
T *at_function_object(QQmlListProperty<T> *property, int index)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedPtrField<T>*>(property->data);
  return repeated_field->Mutable(index);
}

template<typename T>
void clear_function_primitive(QQmlListProperty<T> *property)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedField<T>*>(property->data);
  repeated_field->Clear();
}

template<typename T>
void clear_function_object(QQmlListProperty<T> *property)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedPtrField<T>*>(property->data);
  repeated_field->Clear();
}

template<typename T>
int count_function_primitive(QQmlListProperty<T> *property)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedField<T>*>(property->data);
  return repeated_field->size();
}

template<typename T>
int count_function_object(QQmlListProperty<T> *property)
{
  auto *repeated_field = static_cast<::google::protobuf::RepeatedPtrField<T>*>(property->data);
  return repeated_field->size();
}

} // namespace qml
} // namespace qt
} // namespace protobuf
} // namespace google


#endif // GOOGLE_PROTOBUF_QT_QML_QMLLIST_H__
