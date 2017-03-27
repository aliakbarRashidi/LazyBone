#ifndef LAZYBONE_H
#define LAZYBONE_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QQmlParserStatus>
#include <QQueue>
class QTimer;

class LazyBone : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool inverted READ inverted WRITE setInverted NOTIFY invertedChanged)
    Q_PROPERTY(int preferredToggleTime READ preferredToggleTime WRITE setPreferredToggleTime NOTIFY preferredToggleTimeChanged)
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged)
public:
    explicit LazyBone(QObject *parent = 0);

    QString hostName() const;
    void setHostName(QString hostName);

    quint16 port() const;
    void setPort(quint16 port);

    QString name() const;
    void setName(QString name);

    bool inverted() const;
    void setInverted(bool inverted);

    int preferredToggleTime() const;
    void setPreferredToggleTime(int preferredToggleTime);

    bool powered() const;
    void setPowered(bool powered);

    void classBegin() override;
    void componentComplete() override;

signals:
    void hostNameChanged();
    void portChanged();
    void nameChanged();
    void invertedChanged();
    void preferredToggleTimeChanged();
    void poweredChanged();

private:
    void updatePowered(bool powered);
    void updateSocket();
    void processCommands();

    QString m_hostName;
    quint16 m_port = 2000;
    QString m_name;
    bool m_inverted = false;
    int m_preferredToggleTime = 500;
    bool m_powered = false;
    QTcpSocket m_socket;
    bool m_complete = false;
    QQueue<QByteArray> m_commandQueue;
    QTimer* m_queueTimer;
};

#endif // LAZYBONE_H
