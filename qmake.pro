TEMPLATE = lib

CONFIG += qt plugin

QT += qml

TARGET = commandserverplugin

SOURCES += \
    commandserverplugin.cpp \
    commandserver.cpp

HEADERS += \
    commandserverplugin.hpp \
    commandserver.hpp
                         
target.path = $$[QT_INSTALL_QML]/OSSystems/CommandServer
pluginfiles.files += $$PWD/qmldir
pluginfiles.path = $$[QT_INSTALL_QML]/OSSystems/CommandServer
              
INSTALLS += target pluginfiles
