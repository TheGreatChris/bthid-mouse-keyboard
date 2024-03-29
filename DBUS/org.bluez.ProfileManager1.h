/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p org.bluez.ProfileManager1 org.bluez.ProfileManager1.xml
 *
 * qdbusxml2cpp is Copyright (C) 2019 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef ORG_BLUEZ_PROFILEMANAGER1_H
#define ORG_BLUEZ_PROFILEMANAGER1_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.bluez.ProfileManager1
 */
class OrgBluezProfileManager1Interface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.bluez.ProfileManager1"; }

public:
    OrgBluezProfileManager1Interface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~OrgBluezProfileManager1Interface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> RegisterProfile(const QDBusObjectPath &profile, const QString &uuid, const QVariantMap &options)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(profile) << QVariant::fromValue(uuid) << QVariant::fromValue(options);
        return asyncCallWithArgumentList(QStringLiteral("RegisterProfile"), argumentList);
    }

    inline QDBusPendingReply<> UnregisterProfile(const QDBusObjectPath &profile)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(profile);
        return asyncCallWithArgumentList(QStringLiteral("UnregisterProfile"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace org {
  namespace bluez {
    typedef ::OrgBluezProfileManager1Interface ProfileManager1;
  }
}
#endif
