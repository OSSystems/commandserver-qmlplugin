#include "commandserver.hpp"

#include <QLocalServer>
#include <QLocalSocket>

CommandServer::CommandServer(QObject *parent) : QObject(parent)
{
    m_server = new QLocalServer;
}

void CommandServer::listen(const QString &name)
{
    QLocalServer::removeServer(name);

    m_server->close();
    m_server->listen(name);

    connect(m_server, &QLocalServer::newConnection, [=]() {
        QLocalSocket *socket = m_server->nextPendingConnection();

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

        emit commandReceived(line);
    }
}
