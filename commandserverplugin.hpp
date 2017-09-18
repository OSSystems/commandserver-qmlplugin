#ifndef COMMANDSERVERPLUGIN_HPP
#define COMMANDSERVERPLUGIN_HPP

#include <QQmlExtensionPlugin>
#include <QQmlEngine>

class CommandServerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
};

#endif // COMMANDSERVERPLUGIN_HPP
