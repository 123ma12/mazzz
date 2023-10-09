#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    mainShow();
private slots:
    void on_btn_1_clicked();

    void on_btn_return_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase db;
};

#endif // LOGIN_H
