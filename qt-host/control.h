#ifndef CONTROL_H
#define CONTROL_H
#include <QWidget>

namespace Ui {
class Control;
}

class Control : public QWidget
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = nullptr);
    ~Control();
       Ui::Control *ui;
private slots:
       void on_returnButton_clicked();

private:

};

#endif // CONTROL_H
