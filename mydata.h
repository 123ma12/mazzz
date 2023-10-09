#ifndef MYDATA_H
#define MYDATA_H

#include <QWidget>

namespace Ui {
class Mydata;
}

class Mydata : public QWidget
{
    Q_OBJECT

public:
    explicit Mydata(QWidget *parent = 0);
    ~Mydata();
    QMap<QDate, QString> scheduleMap;
    void addSchedule(const QDate& date, const QString& schedule);
    QString getScheduleForDate(const QDate& selectedDate);
signals:
    funShow();
private slots:
    void dataSelecte();
    void on_btn_set_clicked();

    void on_btn_view_clicked();

private:
    Ui::Mydata *ui;
};

#endif // MYDATA_H
