#ifndef MAINTASKS_H
#define MAINTASKS_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainTasks; }
QT_END_NAMESPACE

class MainTasks : public QMainWindow
{
    Q_OBJECT

public:
    MainTasks(QWidget *parent = nullptr);
    ~MainTasks();

signals:
    void groupAdded(QPushButton* button);

public slots:
    void groupAdd();

private slots:
    void on_button_test_addGroup_clicked();

private:
    Ui::MainTasks *ui;
};
#endif // MAINTASKS_H
