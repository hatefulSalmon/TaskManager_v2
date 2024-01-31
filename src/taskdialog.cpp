#include "headers/group.h"
#include "headers/taskdialog.h"
#include "ui_taskdialog.h"
#include <QDebug>
#include <QVector>
#include <QMessageBox>


TaskDialog::TaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskDialog)

{
    ui->setupUi(this);
}

TaskDialog::~TaskDialog()
{
    delete ui;
}

TaskInfo TaskDialog::get_values(){
    TaskInfo task_info;
    task_info.task_name = ui->edit_name->text();
    task_info.task_group = ui->combo_group->currentIndex();
    task_info.creation_date = ui->edit_creation_date->date();
    task_info.is_complete = ui->checkbox_complete->isChecked();
    task_info.complete_date = ui->edit_complete_date->date();
    return task_info;
}

void TaskDialog::on_button_cancel_clicked()
{
    this->reject();
}

void TaskDialog::on_button_ok_clicked()
{
    if(ui->edit_name->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Task name is empty", "Please enter task name.");
        return;
    }
    this->accept();
}

void TaskDialog::set_groups(QVector<Group*> groups){
    for(int i = 0; i < groups.size(); i++){
        this->ui->combo_group->addItem(groups[i]->get_name());
    }
}

void TaskDialog::on_checkbox_complete_toggled(bool checked)
{
    if(checked){
        ui->edit_complete_date->setEnabled(true);
    }
    else{
        ui->edit_complete_date->setEnabled(false);
    }
}

void TaskDialog::set_dialog_data(TaskInfo task_info){
    ui->edit_name->setText(task_info.task_name);
    ui->combo_group->setCurrentIndex(task_info.task_group);
    ui->edit_creation_date->setDate(task_info.creation_date);
    ui->checkbox_complete->setChecked(task_info.is_complete);
    ui->edit_complete_date->setDate(task_info.complete_date);
}

void TaskDialog::set_dialog_data(QString name, int group, QDate creation_date, bool is_complete, QDate completion_date){
    ui->edit_name->setText(name);
    ui->combo_group->setCurrentIndex(group);
    ui->edit_creation_date->setDate(creation_date);
    ui->checkbox_complete->setChecked(is_complete);
    ui->edit_complete_date->setDate(completion_date);
}

void TaskDialog::lock_group(){
    ui->combo_group->setEnabled(false);
}

