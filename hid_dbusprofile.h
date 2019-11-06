#ifndef DBUSHIDPROFILE_H
#define DBUSHIDPROFILE_H

#include <QObject>
#include <QtDBus>

class HID_DBusProfile : public QObject
{
    Q_OBJECT
public:
    explicit HID_DBusProfile(QObject *parent = nullptr);

    QVariantMap options;

private:
    QString descriptorXML;

public slots:
    void Cancel();
    void NewConnection(const QDBusObjectPath &device, const QDBusUnixFileDescriptor &fd, const QVariantMap &fd_properties);
    void Release();
    void RequestDisconnection(const QDBusObjectPath &device);
};

#endif // DBUSHIDPROFILE_H
