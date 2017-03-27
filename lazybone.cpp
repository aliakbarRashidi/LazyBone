#include "lazybone.h"
#include <QThread>
#include <QTimer>

LazyBone::LazyBone(QObject *parent) : QObject(parent),
    m_queueTimer{new QTimer{this}}
{
    m_queueTimer->setInterval(50);
    connect(m_queueTimer, &QTimer::timeout, this, &LazyBone::processCommands);
}

QString LazyBone::hostName() const
{
    return m_hostName;
}

void LazyBone::setHostName(QString hostName)
{
    if (m_hostName == hostName)
        return;

    m_hostName = hostName;
    emit hostNameChanged();
}

quint16 LazyBone::port() const
{
    return m_port;
}

void LazyBone::setPort(quint16 port)
{
    if (m_port == port)
        return;

    m_port = port;
    emit portChanged();
}

QString LazyBone::name() const
{
    return m_name;
}

void LazyBone::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

bool LazyBone::inverted() const
{
    return m_inverted;
}

void LazyBone::setInverted(bool inverted)
{
    if (m_inverted == inverted)
        return;

    m_inverted = inverted;
    emit invertedChanged();
}

int LazyBone::preferredToggleTime() const
{
    return m_preferredToggleTime;
}

void LazyBone::setPreferredToggleTime(int preferredToggleTime)
{
    if (m_preferredToggleTime == preferredToggleTime)
        return;

    m_preferredToggleTime = preferredToggleTime;
    emit preferredToggleTimeChanged();
}

bool LazyBone::powered() const
{
    return m_powered;
}

void LazyBone::setPowered(bool powered)
{
    QThread::msleep(100);
    m_commandQueue.enqueue(powered ? "e" : "o");
}

void LazyBone::classBegin()
{

}

void LazyBone::componentComplete()
{
    m_complete = true;
    connect(this, &LazyBone::hostNameChanged, this, &LazyBone::updateSocket);
    connect(this, &LazyBone::portChanged, this, &LazyBone::updateSocket);
    updateSocket();
    m_queueTimer->start();
}

void LazyBone::updatePowered(bool powered)
{
    if (m_powered == powered)
        return;

    m_powered = powered;
    emit poweredChanged();
}

void LazyBone::updateSocket()
{
    m_socket.disconnectFromHost();
    m_socket.connectToHost(m_hostName, m_port);
}

void LazyBone::processCommands()
{
    if (m_socket.state() == QAbstractSocket::ConnectedState && !m_commandQueue.isEmpty()) {
        m_socket.write(m_commandQueue.dequeue());
    }
}
