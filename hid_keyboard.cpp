#include "hid_keyboard.h"

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

HID_Keyboard::HID_Keyboard(QObject *parent)
    : QObject(parent),
      controlChannel(QBluetoothServiceInfo::Protocol::L2capProtocol),
      interruptChannel(QBluetoothServiceInfo::Protocol::L2capProtocol),
      testTrigger(this)
{
    connect(&controlChannel, SIGNAL(newConnection()), this, SLOT(incommingControlChannelConnection()));
    connect(&interruptChannel, SIGNAL(newConnection()), this, SLOT(incommingInterruptChannelConnection()));

    connect(&testTrigger, SIGNAL(timeout()), this, SLOT(testTimerExpired()));

    controlSocket = nullptr;
    interruptSocket = nullptr;

    testTrigger.start(1000);
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
    connect(controlSocket, SIGNAL(disconnected()), this, SLOT(disconnectedControlChannel()));
}

void HID_Keyboard::incommingInterruptChannelConnection()
{
    qDebug() << "incommingInterruptChannelConnection()";
    interruptSocket = interruptChannel.nextPendingConnection();
    qDebug() << interruptSocket->peerName() << interruptSocket->peerPort() << interruptSocket->peerAddress();
    connect(interruptSocket, SIGNAL(disconnected()), this, SLOT(disconnectedInterruptChannel()));
}

void HID_Keyboard::readControlChannel()
{
    qDebug() << "HID_Keyboard::readControlChannel()";
}

void HID_Keyboard::readInterruptChannel()
{
    qDebug() << "HID_Keyboard::readInterruptChannel()";
}

void HID_Keyboard::disconnectedControlChannel()
{
    qDebug() << "HID_Keyboard::disconnectedControlChannel()";
}

void HID_Keyboard::disconnectedInterruptChannel()
{
    qDebug() << "HID_Keyboard::disconnectedInterruptChannel()";
}

void HID_Keyboard::testTimerExpired()
{
    qDebug() << "HID_Keyboard::testTimerExpired()";

    if(controlSocket != nullptr){
        qDebug() << "control socket read:" << controlSocket->bytesAvailable();
        QByteArray recv_data = controlSocket->readAll();

        unsigned char cmd_reply[8] = {0x00};

        if(recv_data.size() > 0)
        {
            qDebug() << recv_data;
            switch((recv_data[0] & 0xF0))
            {
            case 0x90:
                qDebug() << "Received SET_IDLE cmd";
                cmd_reply[0] = 0x00;
                if(controlSocket->write((const char*)cmd_reply, 1) == 1)
                    qDebug() << "Reply send";
                else
                    qDebug() << "failed sending reply";

            break;

            default:
                qDebug() << "received unknown cmd";

            }
        }
    }

    if(interruptSocket != nullptr){
        qDebug() << "interrupt socket read:" << interruptSocket->bytesAvailable();

        QByteArray recv_data = interruptSocket->readAll();
        if(recv_data.size() > 0)
        {
            qDebug() << recv_data;
        }
    }

    if(interruptSocket != nullptr)
    {
        unsigned char test_data[9] =
        {
            0xA1,
            0x00, 0x00,
            0x2C, 'a'+1, 'a'+2,
            'a'+3, 'a'+10, 'a'+20
        };

        if(interruptSocket->write((const char*)test_data, 9) != 9)
            qDebug() << "failed sending report";
        else
            qDebug() << "send report success";

    }

}
