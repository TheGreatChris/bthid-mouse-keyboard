#include <QCoreApplication>
#include <QDebug>
#include <QProcess>

#include "DBUS/org.bluez.Adapter1.h"
#include "hid_keyboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QProcess hciconfig;
    hciconfig.start("hciconfig hci0 down");
    hciconfig.waitForFinished();
    if(hciconfig.exitCode() != 0)
        qDebug() << "Error Output" << hciconfig.readAllStandardError();

    hciconfig.start("hciconfig hci0 up");
    hciconfig.waitForFinished();
    if(hciconfig.exitCode() != 0)
        qDebug() << "Error Output" << hciconfig.readAllStandardError();

    hciconfig.start("hciconfig hci0 name raspi-mouse");
    hciconfig.waitForFinished();
    if(hciconfig.exitCode() != 0)
        qDebug() << "Error Output" << hciconfig.readAllStandardError();

    hciconfig.start("hciconfig hci0 class 0x0005C0");
    hciconfig.waitForFinished();
    if(hciconfig.exitCode() != 0)
        qDebug() << "Error Output" << hciconfig.readAllStandardError();

    qDebug() << hciconfig.readAllStandardOutput();

    org::bluez::Adapter1 adapter1("org.bluez", "/org/bluez/hci0", QDBusConnection::systemBus());
    if(adapter1.isValid() == false)
        qDebug() << "Adapter1 interface not connected";

    qDebug() << "Name:" << adapter1.name();
    qDebug() << "Class:" << adapter1._class();
    qDebug() << "Powered:" << adapter1.powered();
    qDebug() << "Discoverable" << adapter1.discoverable();

    HID_Keyboard kbd(&a);
    kbd.startServer();

    return a.exec();
}
