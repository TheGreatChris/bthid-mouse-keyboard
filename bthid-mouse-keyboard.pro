QT -= gui
QT += dbus bluetooth

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    DBUS/org.bluez.Adapter1.cpp \
    hid_keyboard.cpp \
    DBUS/org.bluez.ProfileManager1.cpp \
    DBUS/org.bluez.Profile1.cpp \
    hid_dbusprofile.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DBUS/org.bluez.Adapter1.h \
    hid_keyboard.h \
    DBUS/org.bluez.ProfileManager1.h \
    DBUS/org.bluez.Profile1.h \
    hid_dbusprofile.h

DISTFILES += \
    sdp_service_record.xml
