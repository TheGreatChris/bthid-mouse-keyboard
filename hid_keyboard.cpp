#include "hid_keyboard.h"

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

HID_Keyboard::HID_Keyboard(QObject *parent)
    : QObject(parent),
      controlChannel(QBluetoothServiceInfo::Protocol::L2capProtocol),
      interruptChannel(QBluetoothServiceInfo::Protocol::L2capProtocol)
{
    connect(&controlChannel, SIGNAL(newConnection()), this, SLOT(incommingControlChannelConnection()));
    connect(&interruptChannel, SIGNAL(newConnection()), this, SLOT(incommingInterruptChannelConnection()));
}

bool HID_Keyboard::startServer()
{
    qDebug() << "Control listen" << controlChannel.listen(QBluetoothAddress("00:00:00:00:00:00"), 17);
    qDebug() << "Interrupt listen" << interruptChannel.listen(QBluetoothAddress("00:00:00:00:00:00"), 19);
    if(controlChannel.error() != QBluetoothServer::NoError || interruptChannel.error() != QBluetoothServer::NoError){
        qDebug() << "Control channel error:" << controlChannel.error();
        qDebug() << "Interrupt channel error:" << interruptChannel.error();
        return false;
    }

    return true;
}

void HID_Keyboard::incommingControlChannelConnection()
{
    qDebug() << "incommingControlChannelConnection()";
    controlSocket = controlChannel.nextPendingConnection();
    qDebug() << controlSocket->peerName() << controlSocket->peerPort() << controlSocket->peerAddress();
}

void HID_Keyboard::incommingInterruptChannelConnection()
{
    qDebug() << "incommingInterruptChannelConnection()";
    interruptSocket = interruptChannel.nextPendingConnection();
    qDebug() << interruptSocket->peerName() << interruptSocket->peerPort() << interruptSocket->peerAddress();
}

void HID_Keyboard::readControlChannel()
{
    qDebug() << "HID_Keyboard::readControlChannel()";
}

void HID_Keyboard::readInterruptChannel()
{
    qDebug() << "HID_Keyboard::readInterruptChannel()";
}
