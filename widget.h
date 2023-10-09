#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <login.h>
#include <function.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btn_login_clicked();

    void on_btn_enroll_clicked();

    void mainShow();

private:
    Ui::Widget *ui;
    Login *mylogin;
    Function *myfun;
    QSqlDatabase db;
};

#endif // WIDGET_H
