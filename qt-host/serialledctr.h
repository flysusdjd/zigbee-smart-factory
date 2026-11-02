#ifndef SERIALLEDCTR_H
#define SERIALLEDCTR_H

#include <QMainWindow>
//user
#include <QSerialPort>
#include <QLabel>
#include <QDebug>
#include <QSerialPortInfo>
#include <QTime>//定时器
#include <qtextcodec.h>


namespace Ui {
class SerialLedCtr;
}

class SerialLedCtr : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialLedCtr(QWidget *parent = nullptr);
    ~SerialLedCtr();

private slots:
    //void receve_data();
    void recvSLOTS();

    void on_btn_dis_clicked();

    void on_btn_OpenCom_clicked();

    void on_btn_CloseCom_clicked();

    void on_ClearButton_clicked();

    void on_pushButton_Send_clicked();

    void on_OnButton_2_clicked();

    void on_OnButton_clicked();

    void on_OnButton_3_clicked();

    void on_OffButton_clicked();

    void on_OffButton_2_clicked();

    void on_OffButton_3_clicked();

    void on_changeButton_clicked();

    void on_change2Button_clicked();

    void on_change3Button_clicked();

private:
    Ui::SerialLedCtr *ui;
    //user
    QSerialPort *serialPort ;
    void sendCommand(uint8_t deviceid, uint8_t cmdcode, uint8_t tempTh , uint8_t mq2Th );

};

#endif // SERIALLEDCTR_H
