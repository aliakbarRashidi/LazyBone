#include "lazybone.h"
#include <QThread>

LazyBone::LazyBone(QObject *parent) : QObject(parent)
{

}

QString LazyBone::address() const
{
    return m_address;
}

void LazyBone::setAddress(QString address)
{
    if (m_address == address)
        return;

    m_address = address;
    emit addressChanged();
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
    m_socket.connectToHost(m_address, m_port);
    QThread::msleep(100);
    m_socket.write(powered ? "e" : "o");
}

void LazyBone::updatePowered(bool powered)
{
    if (m_powered == powered)
        return;

    m_powered = powered;
    emit poweredChanged();
}
