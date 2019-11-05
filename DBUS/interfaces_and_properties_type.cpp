#include "interfaces_and_properties_type.h"

QDBusArgument &operator<<(QDBusArgument &argument, const interfaces_and_properties_type &x)
{
    argument.beginMap(QVariant::String, QVariant::Map);
    argument.endMap();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, interfaces_and_properties_type &x)
{
    return argument;
}

void interfaces_and_properties_type::registerMetaType()
{
    qRegisterMetaType<interfaces_and_properties_type>("interfaces_and_properties_type");
    qDBusRegisterMetaType<interfaces_and_properties_type>();
}
