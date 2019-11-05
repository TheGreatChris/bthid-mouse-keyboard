#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <QObject>

#include <QBluetoothServer>


class HID_Keyboard : public QObject
{
    Q_OBJECT
public:
    explicit HID_Keyboard(QObject *parent = nullptr);

signals:

public slots:
    bool startServer();
    void incommingControlChannelConnection();
    void incommingInterruptChannelConnection();

private:
    QBluetoothServer controlChannel;
    QBluetoothServer interruptChannel;
};

#endif // HID_KEYBOARD_H
