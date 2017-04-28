#Protobuf-Qt

This lib should help with usage of generated sources from Google Protobuf files with Qt and QML.

###Idea

+ Replace std::string by QString
+ Mark all messages classes as QObject
+ Add Q_PROPERTY for all messages fields
    - Wrap repeated fields by QQmlListProperty
    - Add signals for fields changes

###Usage

+ Build compiler
+ Generate sources; example command:
```sh
    protoc --plugin=protoc-gen-qt=protoc-gen-qt --qt_out=. Test.proto
```
+ Add generated sources and support headers (from *include* path) to your project
+ Profit
