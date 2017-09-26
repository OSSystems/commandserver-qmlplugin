#ifndef COMMANDSERVER_HPP
#define COMMANDSERVER_HPP

#include <QObject>

class QLocalServer;
class QLocalSocket;

class CommandServer : public QObject
{
    Q_OBJECT

public:
    CommandServer(QObject *parent = nullptr);

public slots:
    void listen(const QString &name);

    void sendReply(const QString &reply);

signals:
    void nameChanged(const QString &name);
    void commandReceived(const QString &command, const QStringList &args);

private:
    QLocalServer *m_server;
    QLocalSocket *m_socket;

    void parseData(QLocalSocket *socket, const QByteArray &data);
};

#endif // COMMANDSERVER_HPP
