# Protobuf-Qt

This lib should help with usage of generated sources from Google Protobuf files with Qt and QML.

### Idea
Just write plugin for current C++ generator:

+ Add getter/setter for std::string as QString
+ Mark all messages classes as QObject
+ Add Q_PROPERTY for all messages fields
    - Wrap repeated fields by QQmlListProperty
    - Add signals for fields changes

### Usage

+ Build compiler
+ Generate sources; example command:
```sh
    protoc --plugin=protoc-gen-qt=protoc-gen-qt --cpp_out=. --qt_out=. Test.proto
```
+ Profit
