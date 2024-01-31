#ifndef GROUP_H
#define GROUP_H

#include <QWidget>
#include "headers/task.h"
namespace Ui {
class Group;
}

class Group : public QWidget
{
    Q_OBJECT

signals:
    void creatingTask(Group* group);
public:
    explicit Group(QWidget *parent = nullptr);
    void addTaskToUi(Task* task);
    ~Group();
    QString get_name();
    void removeTaskFromUi(Task* task);

public slots:
    void setGroupName(QString new_name);

private slots:
    void on_button_addTask_clicked();

private:
    Ui::Group *ui;
};

#endif // GROUP_H
