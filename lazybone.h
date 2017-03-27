#ifndef LAZYBONE_H
#define LAZYBONE_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

class LazyBone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool inverted READ inverted WRITE setInverted NOTIFY invertedChanged)
    Q_PROPERTY(int preferredToggleTime READ preferredToggleTime WRITE setPreferredToggleTime NOTIFY preferredToggleTimeChanged)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit LazyBone(QObject *parent = 0);

    QString address() const;
    void setAddress(QString address);

    quint16 port() const;
    void setPort(quint16 port);

    QString name() const;
    void setName(QString name);

    bool inverted() const;
    void setInverted(bool inverted);

    int preferredToggleTime() const;
    void setPreferredToggleTime(int preferredToggleTime);

    bool state() const;
    void setState(bool state);

signals:
    void addressChanged();
    void portChanged();
    void nameChanged();
    void invertedChanged();
    void preferredToggleTimeChanged();
    void stateChanged();

private:
    void updateState(bool state);

    QString m_address;
    quint16 m_port = 2000;
    QString m_name;
    bool m_inverted = false;
    int m_preferredToggleTime = 500;
    bool m_state = false;
    QTcpSocket m_socket;
};

#endif // LAZYBONE_H
