#include "commandserverplugin.hpp"
#include "commandserver.hpp"

void CommandServerPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("CommandServer"));
    qmlRegisterType<CommandServer>(uri, 1, 0, "CommandServer");
}
