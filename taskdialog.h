#ifndef TASKDIALOG_H
#define TASKDIALOG_H
#include <QDialog>
#include <QVector>
#include <QDate>
#include "group.h"

namespace Ui {
class TaskDialog;
}

class TaskDialog : public QDialog
{
    Q_OBJECT

signals:
    void task_accepted(TaskInfo task_info);

public:
    explicit TaskDialog(QWidget *parent = nullptr);
    void set_dialog_data(TaskInfo task_info);
    void set_dialog_data(QString name, int group, QDate creation_date, bool is_complete, QDate completion_date);
    ~TaskDialog();
    void set_groups(QVector<Group*> groups);
    TaskInfo get_values();
    void lock_group();

private slots:
    void on_button_cancel_clicked();
    void on_button_ok_clicked();

    void on_checkbox_complete_toggled(bool checked);

private:
    Ui::TaskDialog *ui;

};

#endif // TASKDIALOG_H
