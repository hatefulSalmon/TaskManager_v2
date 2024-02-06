#ifndef MAINTASKS_H
#define MAINTASKS_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QStackedWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include "task.h"
#include "taskdialog.h"
#include "headers/group.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainTasks; }
QT_END_NAMESPACE

class MainTasks : public QMainWindow
{
    Q_OBJECT

public:
    QVector<Task*> all_tasks;
    QVector<Group*> all_groups;
    QStackedWidget* stack;


    MainTasks(QWidget *parent = nullptr);
    ~MainTasks();

signals:
    void groupAdded(QPushButton* button);

public slots:
    //Group actions
    void groupAdd();

    //Task actions
    void taskCreate(TaskInfo task_info);
    void taskAddFromGroupped(Group* group);
    void taskAddFromUngroupped();
    void taskEdit(Task* task);
    void taskDelete(Task* task);
    void taskComplete(Task* task);
    void taskUncomplete(Task* task);

private slots:

    void on_actionView_unsorted_triggered();

    void on_actionSort_by_group_triggered();

    void on_actionView_completed_tasks_triggered();

    void on_actionNew_user_triggered();

private:
    int getGroupIndex(QString group_name);
    void addGroupToUi(Group* group);
    void addTaskToGroupUi(Task* task);
    void addTaskToUngrouppedUi(Task* task);
    void setUpGroupped();
    void setUpUngroupped();
    void setUpComplete();

    QJsonObject save_data;
    Ui::MainTasks *ui;

};
#endif // MAINTASKS_H
