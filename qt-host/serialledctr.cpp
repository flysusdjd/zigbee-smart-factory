#include "serialledctr.h"
#include "ui_serialledctr.h"

SerialLedCtr::SerialLedCtr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialLedCtr),
    serialPort(new QSerialPort(this))  // 初始化 serialPort
{
    ui->setupUi(this);
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    for(int i =0 ;i<list.size(); i++)
    {
        ui->pT_MesageDis->appendPlainText(list.at(i).portName());
         ui->cB_choseBaudRate->setCurrentIndex(10);

    }
    //创建窗口类对象
    serialPort = new QSerialPort;
     connect(serialPort, &QSerialPort::readyRead, this, &SerialLedCtr::recvSLOTS);
     connect(ui->ClearButton, &QPushButton::clicked, this, &SerialLedCtr::on_ClearButton_clicked);
    // connect(ui->OnButton, &QPushButton::clicked, this, &SerialLedCtr::on_OnButton_clicked);
      //  connect(ui->OffButton, &QPushButton::clicked, this, &SerialLedCtr::on_OffButton_clicked);
        connect(ui->pushButton_Send, &QPushButton::clicked, this, &SerialLedCtr::on_pushButton_Send_clicked);
       connect(ui->changeButton, &QPushButton::clicked, this, &SerialLedCtr::on_changeButton_clicked);
       connect(ui->change2Button, &QPushButton::clicked, this, &SerialLedCtr::on_change2Button_clicked);
       connect(ui->change3Button, &QPushButton::clicked, this, &SerialLedCtr::on_change3Button_clicked);

}

SerialLedCtr::~SerialLedCtr()
{
    delete ui;
}


// 串口发现函数
void SerialLedCtr::on_btn_dis_clicked()
{
    ui->cB_choseCom->clear();
    ui->pT_MesageDis->appendPlainText("发现以下串口:");
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->cB_choseCom->addItem(info.portName());
        ui->pT_MesageDis->appendPlainText(info.portName());
    }
}

// 打开串口
void SerialLedCtr::on_btn_OpenCom_clicked()
{
    QString strCom = ui->cB_choseCom->currentText();          // 串口号
    QString sBaudRate = ui->cB_choseBaudRate->currentText();  // 波特率
    QString strCheck = ui->cB_checkBit->currentText();        // 校验位
    QString strData = ui->cB_dataBit->currentText();          // 数据位
    QString strStop = ui->cB_stopBit->currentText();          // 停止位

    if (strCom != "") {
        serialPort->setPortName(strCom); // 设置串口
        serialPort->setBaudRate(sBaudRate.toInt());
        if (serialPort->open(QIODevice::ReadWrite)) {
            ui->text_MsgCom->setStyleSheet("color:green");
            ui->text_MsgCom->setText("串口打开成功 " + strCom + " " + sBaudRate + " " + strCheck + " " + strData + " " + strStop);
        } else {
            ui->text_MsgCom->setStyleSheet("color:red");
            ui->text_MsgCom->setText("串口打开失败！！！");
        }
    } else {
        ui->text_MsgCom->setStyleSheet("color:red");
        ui->text_MsgCom->setText("串口打开失败！！！");
    }
}

// 关闭串口函数
void SerialLedCtr::on_btn_CloseCom_clicked()
{
    serialPort->close();
    ui->text_MsgCom->setStyleSheet("color:green");
    ui->text_MsgCom->setText("串口关闭成功");
}



void SerialLedCtr::on_ClearButton_clicked()
{
    ui->pT_MesageDis->clear();
}


void SerialLedCtr::recvSLOTS()
{
    // 读取串口数据
    QByteArray data = serialPort->readAll();
     ui->pT_MesageDis->appendPlainText("接收:" + data);
     qDebug() << "Invalid arraydata received: " << data;
    if (data.size() < 11) {
        qDebug() << "No data received from the serial port" << data;
        return;
    }

    qDebug() << "Raw data received:" << data;

    // 将字节数组转换为字符串
    QString dataStr = QString::fromUtf8(data);

    // 打印转换后的字符串
    qDebug() << "Converted data:" << dataStr;

    // 假设您的数据包以特定格式传递，我们将使用正则表达式解析数据包
    QRegExp rx("E(\\d+) T:(\\d+) H:(\\d+) L:(\\d+) MQ2:(\\d+) P:(\\w+)");
    if (rx.indexIn(dataStr) != -1)
    {
        int id = rx.cap(1).toInt();
        int temperature = rx.cap(2).toInt();
        int humidity = rx.cap(3).toInt();
        int light = rx.cap(4).toInt();
        int gas = rx.cap(5).toInt();
        QString human = rx.cap(6);

        // 显示数据
        switch (id) {
            case 1:
                // 显示终端1的数据
                ui->line_temp->setText(QString(" %1 °C").arg(temperature));
                ui->line_Humi->setText(QString(" %1 %").arg(humidity));
                ui->line_people->setText(QString(" %1").arg(human == "Yes" ? "Detected" : "Not detected"));
                ui->line_yan->setText(QString(" %1 %").arg(gas));
                break;
            case 2:
                // 显示终端2的数据
                ui->line_temp_2->setText(QString(" %1 °C").arg(temperature));
                ui->line_Humi_2->setText(QString(" %1 %").arg(humidity));
                ui->line_people_2->setText(QString(" %1").arg(human == "Yes" ? "Detected" : "Not detected"));
               ui->line_yan_2->setText(QString(" %1 %").arg(gas));
                break;
            case 3:
                // 显示终端3的数据
                ui->line_temp_3->setText(QString(" %1 °C").arg(temperature));
                ui->line_Humi_3->setText(QString(" %1 %").arg(humidity));
                ui->line_people_3->setText(QString(" %1").arg(human == "Yes" ? "Detected" : "Not detected"));
                ui->line_yan_3->setText(QString(" %1 %").arg(gas));
                break;
            default:
                // 未知的终端 ID
                qDebug() << "Unknown terminal ID:" << id;
                break;
        }
    }
    else
    {
        qDebug() << "Data format error";
    }
}



void SerialLedCtr::sendCommand(uint8_t deviceid, uint8_t cmdcode, uint8_t tempTh , uint8_t mq2Th )
{
    QByteArray data;
    data.append(0xAA);
    data.append(0x55);
    data.append(0x11);
    data.append(0x15);
    data.append(deviceid);
    data.append(cmdcode);
    data.append(tempTh); // 温度阈值
    data.append(mq2Th);  // MQ2 阈值
    data.append(0x01);

    serialPort->write(data);
    ui->pT_MesageDis->appendPlainText("发送: " + data.toHex());
}

void SerialLedCtr::on_pushButton_Send_clicked()
{
    QString dataToSend = ui->lineEdit_SendData->text(); // 从文本框获取数据
        if (serialPort->isOpen() && !dataToSend.isEmpty()) {
            serialPort->write(dataToSend.toUtf8()); // 发送数据到串口
            ui->pT_MesageDis->appendPlainText("发送: " + dataToSend); // 显示发送的数据
        } else {
            ui->pT_MesageDis->appendPlainText("串口未打开或无数据发送");
        }
}





void SerialLedCtr::on_OnButton_clicked()
{
    sendCommand(1, 0x02, 0,0);
}


void SerialLedCtr::on_OnButton_2_clicked()
{
    sendCommand(2, 0x02,0,0);
}

void SerialLedCtr::on_OnButton_3_clicked()
{
    sendCommand(3, 0x02,0,0);
}

void SerialLedCtr::on_OffButton_clicked()
{
     sendCommand(1, 0x03,0,0);
}

void SerialLedCtr::on_OffButton_2_clicked()
{
     sendCommand(2, 0x03,0,0);
}

void SerialLedCtr::on_OffButton_3_clicked()
{
     sendCommand(3, 0x03,0,0);
}

void SerialLedCtr::on_changeButton_clicked()
{
    {
        uint8_t deviceid = 1; // 假设要更新终端1的阈值，你可以根据需要进行更改
        uint8_t cmdcode = 0x01; // 更新阈值的命令码

        // 从UI获取阈值
        uint8_t tempTh = ui->lineEdit_temp->text().toUInt();
        uint8_t mq2Th = ui->lineEdit_mq2->text().toUInt();

        sendCommand(deviceid, cmdcode, tempTh, mq2Th);
    }
}

void SerialLedCtr::on_change2Button_clicked()
{
    {
        uint8_t deviceid = 2; // 假设要更新终端1的阈值，你可以根据需要进行更改
        uint8_t cmdcode = 0x01; // 更新阈值的命令码

        // 从UI获取阈值
        uint8_t tempTh = ui->lineEdit_temp_2->text().toUInt();
        uint8_t mq2Th = ui->lineEdit_mq2_2->text().toUInt();

        sendCommand(deviceid, cmdcode, tempTh, mq2Th);
    }
}

void SerialLedCtr::on_change3Button_clicked()
{
    {
        uint8_t deviceid = 3; // 假设要更新终端1的阈值，你可以根据需要进行更改
        uint8_t cmdcode = 0x01; // 更新阈值的命令码

        // 从UI获取阈值
        uint8_t tempTh = ui->lineEdit_temp_3->text().toUInt();
        uint8_t mq2Th = ui->lineEdit_mq2_3->text().toUInt();

        sendCommand(deviceid, cmdcode, tempTh, mq2Th);
    }
}
