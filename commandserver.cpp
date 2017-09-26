#include "commandserver.hpp"

#include <QLocalServer>
#include <QLocalSocket>

CommandServer::CommandServer(QObject *parent) : QObject(parent)
{
    m_server = new QLocalServer;
    m_socket = NULL;
}

void CommandServer::listen(const QString &name)
{
    QLocalServer::removeServer(name);

    m_server->close();
    m_server->listen(name);

    connect(m_server, &QLocalServer::newConnection, [=]() {
        QLocalSocket *socket = m_server->nextPendingConnection();

        if (m_socket) {
            qWarning("CommandServer: simultaneous connections are not supported");
            socket->close();
            return;
        }

        connect(socket, &QLocalSocket::disconnected, [=]() {
            socket->deleteLater();
            m_socket = NULL;
        });

        connect(socket, &QLocalSocket::readyRead, [=]() {
            parseData(socket, socket->readAll());
        });
    });
}

void CommandServer::sendReply(const QString &reply)
{
    if (!m_socket || !m_socket->isValid())
        return;

    m_socket->write(reply.toLocal8Bit());
    m_socket->close();
}

void CommandServer::parseData(QLocalSocket *socket, const QByteArray &data)
{
    QStringList lines = QString::fromLocal8Bit(data).split('\n');

    foreach (const QString &line, lines) {
        if (line.isEmpty())
            continue;

        m_socket = socket;

        QStringList args = line.split(' ');

        emit commandReceived(args.first(), args.mid(1, -1));
    }
}
