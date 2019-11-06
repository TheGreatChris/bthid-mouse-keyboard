#include <QCoreApplication>
#include <QDebug>
#include <QProcess>

#include "DBUS/org.bluez.Adapter1.h"
#include "DBUS/org.bluez.ProfileManager1.h"
#include "DBUS/org.bluez.Profile1.h"

#include "hid_dbusprofile.h"
#include "hid_keyboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Resetting hci0 adapter...";

    QProcess hciconfig;
    hciconfig.start("hciconfig hci0 down");
    hciconfig.waitForFinished();
    if(hciconfig.exitCode() != 0)
        qDebug() << hciconfig.program() << "Error Output" << hciconfig.readAllStandardError();

    hciconfig.start("hciconfig hci0 up");
    hciconfig.waitForFinished();
    if(hciconfig.exitCode() != 0)
        qDebug() << hciconfig.program() << "Error Output" << hciconfig.readAllStandardError();

    qDebug() << "    Finished" << hciconfig.readAllStandardOutput();

    org::bluez::Adapter1 adapter1("org.bluez", "/org/bluez/hci0", QDBusConnection::systemBus());
    if(adapter1.isValid() == false)
        qDebug() << "Adapter1 interface not connected";

    org::bluez::ProfileManager1 profileManager1("org.bluez", "/org/bluez", QDBusConnection::systemBus());
    if(profileManager1.isValid() == false)
        qDebug() << "ProfileManager1 interface not connected";

    qDebug() << "Name:" << adapter1.name();
    qDebug() << "Class:" << adapter1._class();
    qDebug() << "Powered:" << adapter1.powered();
    qDebug() << "Discoverable" << adapter1.discoverable();

    HID_DBusProfile profile(&a);
    Profile1Adaptor dbusAdaptor(&profile);

    if(QDBusConnection::systemBus().registerObject("/", &profile) == true)
        qDebug() << "HID_Profile registered as DBus object";
    else
        qDebug() << "HID_Profile registration as DBus object failed";

    QDBusPendingReply<> reply = profileManager1.RegisterProfile(QDBusObjectPath("/"), "32749074-11e0-4145-925d-5a6ffd8b488f", profile.options);
    reply.waitForFinished();
    if(reply.isError())
        qDebug() << reply.reply() << ":" << reply.error();
    else
        qDebug() << reply.reply();


    HID_Keyboard kbd(&a);
    kbd.startServer();

    return a.exec();
}
