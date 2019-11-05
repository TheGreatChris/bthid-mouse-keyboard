#ifndef INTERFACES_AND_PROPERTIES_TYPE_H
#define INTERFACES_AND_PROPERTIES_TYPE_H

#include <QtDBus>
#include <QMap>
#include <QString>

struct interfaces_and_properties_type
{
    QMap<QString, QMap<QString, QDBusVariant>> interfaces_and_properties;

    static void registerMetaType();
};

Q_DECLARE_METATYPE(interfaces_and_properties_type)

QDBusArgument &operator<<(QDBusArgument &argument, const interfaces_and_properties_type &x);
const QDBusArgument &operator>>(const QDBusArgument &argument, interfaces_and_properties_type &x);

#endif // INTERFACES_AND_PROPERTIES_TYPE_H
