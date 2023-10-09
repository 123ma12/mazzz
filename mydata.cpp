#include <QMessageBox>
#include "mydata.h"
#include "ui_mydata.h"
#include <QInputDialog>

Mydata::Mydata(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mydata)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());//设置固定大小
    this->setWindowIcon(QIcon(":/picture/03_data.png"));
    this->setWindowTitle("日历");
    connect(ui->calendarWidget,SIGNAL(selectionChanged()),this,SLOT(dataSelecte()));
}

Mydata::~Mydata()
{
    delete ui;
}
void Mydata::dataSelecte()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    // 执行行程安排操作，比如弹出对话框并显示所选日期
    //QMessageBox::information(this, "行程安排", "您选择了日期：" + selectedDate.toString(Qt::ISODate));
    // 弹出对话框让用户输入行程信息
    //QString schedule = QInputDialog::getText(this, "添加行程", "请输入行程信息");

    // 将行程信息添加到相应的日期处
    // 这里可以根据具体需求将日期和行程信息存储到数据结构或进行其他操作
//    QString existingSchedule = QString::fromStdString(ui->calendarWidget->dateTextFormat(selectedDate).string());
//    ui->calendarWidget->setDateTextFormat(selectedDate, QTextCharFormat());
//    ui->calendarWidget->setDateTextFormat(selectedDate, QTextCharFormat(), QColor(Qt::red));
//    ui->calendarWidget->setDateTextFormat(selectedDate, QTextCharFormat(), QColor(Qt::white));

    // 判断日期上是否已存在行程信息
#if 0
    if (ui->calendarWidget->dateTextFormat(selectedDate).background().color() == Qt::red)
    {
//        QMessageBox::information(this, "行程已存在", "日期为 " + selectedDate.toString() + " 的行程已存在！请在现有行程上进行修改。");
//        QString schedule = ui->calendarWidget->dateTextFormat(selectedDate).toolTip();
        QMessageBox::information(this, "行程信息", "日期为 " + selectedDate.toString() + " 的行程：" + schedule);
        return;
    }

    // 将行程信息添加到相应的日期处
    // 这里可以根据具体需求将日期和行程信息存储到数据结构或进行其他操作
    QTextCharFormat format;
    format.setBackground(QColor(Qt::red));
    format.setForeground(QColor(Qt::white));
    ui->calendarWidget->setDateTextFormat(selectedDate, format);
    QMessageBox::information(this, "行程添加成功", "日期为 " + selectedDate.toString() + " 的行程：" + schedule + " 已成功添加！");
#endif
}

void Mydata::on_btn_set_clicked() //设置行程
{
    QDate selectedDate = ui->calendarWidget->selectedDate();

    // 弹出对话框让用户输入行程信息
    QString schedule = QInputDialog::getText(this, "设置行程", "请输入行程信息");
//    qDebug() << schedule;
    //将行程添加到数据结构当中
    addSchedule(selectedDate,schedule);

    // 将行程信息与所选日期关联，可以使用数据结构或其他方式进行存储/管理

    if(schedule.isEmpty())  //判断是否添加了行程
    {
        return;
    }
    QTextCharFormat format;
    format.setBackground(QColor(Qt::green));
    format.setForeground(QColor(Qt::white));
    ui->calendarWidget->setDateTextFormat(selectedDate, format);

//    QMessageBox::information(this, "行程设置成功", "日期为 " + selectedDate.toString() + " 的行程：" + schedule + " 已成功设置！");
}


void Mydata::on_btn_view_clicked()  //查看行程
{
    QDate selectedDate = ui->calendarWidget->selectedDate();

    // 获取与所选日期关联的行程信息

    QString schedule = getScheduleForDate(selectedDate);

    if (!schedule.isEmpty())
    {
        // 显示行程信息
        QMessageBox::information(this, "行程信息", "日期为 " + selectedDate.toString() + " 的行程：" + schedule);
    }
    else
    {
        QMessageBox::information(this, "行程信息", "日期为 " + selectedDate.toString() + " 的行程不存在。");
    }
}
void Mydata::addSchedule(const QDate& date, const QString& schedule)
{
    if(schedule.isEmpty())
    {
        return;
    }
    scheduleMap.insert(date, schedule);
    QMessageBox::information(this, "行程添加成功", "日期为 " + date.toString() + " 的行程：" + schedule + " 已成功添加！");
}

QString Mydata::getScheduleForDate(const QDate& selectedDate)
{
    if (scheduleMap.contains(selectedDate))
    {
        return scheduleMap.value(selectedDate);
    }
    else
    {
        return QString(); // 如果行程不存在，返回一个空字符串
    }
}
