#include "hid_dbusprofile.h"
#include "QDebug"

HID_DBusProfile::HID_DBusProfile(QObject *parent) : QObject(parent)
{

//    string Name
//        Human readable name for the profile
    options.insert("Name", "bthid-mouse-keyboard");


//    string Service
//        The primary service class UUID (if different from the actual profile UUID)

//    string Role
//        For asymmetric profiles that do not have UUIDs available to uniquely
//        identify each side this parameter allows specifying the precise local role.
//        Possible values: "client", "server"
    options.insert("Role", "server");


//    uint16 Channel
//        RFCOMM channel number that is used for client and server UUIDs.
//        If applicable it will be used in the SDP record as well.

//    uint16 PSM
//        PSM number that is used for client and server UUIDs.
//        If applicable it will be used in the SDP record as well.


//    boolean RequireAuthentication
//        Pairing is required before connections will be established. No devices will be connected if not paired.
    options.insert("RequireAuthentication", false);

//    boolean RequireAuthorization
//        Request authorization before any connection will be established.
    options.insert("RequireAutorization", false);

//    boolean AutoConnect
//        In case of a client UUID this will force connection of the RFCOMM or L2CAP channels when a remote device is connected.
    options.insert("AutoConnect", false);

//    string ServiceRecord
//        Provide a manual SDP record.
    QFile sdp_record("sdp_service_record.xml");
    if(!sdp_record.exists()){
        qDebug() << "Couldn't load sdp record:" << sdp_record.fileName();
    }
    sdp_record.open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text);
    if(!sdp_record.isOpen()){
        qDebug() << "Couldn't open file" << sdp_record.errorString();
    }
    qDebug() << "sdp_record" << sdp_record.fileName() << "Size" << sdp_record.size();
    options.insert("ServiceRecord", QString(sdp_record.readAll()));

//    uint16 Version
//        Profile version (for SDP record)
    options.insert("Version", (uint16_t)0x0001);

//    uint16 Features
//        Profile features (for SDP record)
}

void HID_DBusProfile::Cancel()
{
    qDebug() << "void DBusHIDProfile::Cancel";
}

void HID_DBusProfile::NewConnection(const QDBusObjectPath &device, const QDBusUnixFileDescriptor &fd, const QVariantMap &fd_properties)
{
    qDebug() << "void DBusHIDProfile::NewConnection";
    Q_UNUSED(device)
    Q_UNUSED(fd)
    Q_UNUSED(fd_properties)
}

void HID_DBusProfile::Release()
{
    qDebug() << "void DBusHIDProfile::Release";
}

void HID_DBusProfile::RequestDisconnection(const QDBusObjectPath &device)
{
    qDebug() << "void DBusHIDProfile::RequestDisconnection";
    Q_UNUSED(device)
}
