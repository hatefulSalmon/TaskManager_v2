#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QDate>

struct TaskInfo{
    QString task_name;
    int task_group;
    QDate creation_date;
    bool is_complete;
    QDate complete_date;
};

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT
signals:
    void taskEdit(Task* task);
    void taskDelete(Task* task);

public:
    //Getters
    QString getName();
    QString getGroup();
    QDate getCreationDate();
    bool isComplete();
    QDate getCompletionDate();

    //Setters
    void setName(QString name);
    void setGroup(QString group);
    void setCreationDate(QDate creation_date);
    void setStatus(bool is_complete);
    void setCompletionDate(QDate completion_date);
    void setData(QString name, QString group, QDate creation_date, bool is_complete, QDate completion_date);

    void updateUI();

    explicit Task(QWidget *parent = nullptr);
    ~Task();

private slots:
    void on_button_Edit_clicked();

    void on_button_Delete_clicked();

private:
    QString task_name;
    QString task_group;
    QDate creation_date;
    bool is_complete;
    QDate completion_date;
    Ui::Task *ui;
};

#endif // TASK_H
