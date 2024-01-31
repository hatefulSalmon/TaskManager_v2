#include "headers/group.h"
#include "ui_group.h"
#include "headers/task.h"
#include "headers/taskdialog.h"

#include <QVBoxLayout>
#include <QDebug>
Group::Group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Group)
{
    ui->setupUi(this);
    QWidget* container = new QWidget(this);
    new QVBoxLayout(container);
    ui->scrollarea_tasks->setWidget(container);
}

Group::~Group()
{
    delete ui;
}

void Group::on_button_addTask_clicked()
{
    emit creatingTask(this);
}

void Group::setGroupName(QString new_name){
    ui->label_groupName->setText(new_name);
}

QString Group::get_name(){
    return ui->label_groupName->text();
}

void Group::addTaskToUi(Task* task){
    ui->scrollarea_tasks->widget()->layout()->addWidget(task);
}

void Group::removeTaskFromUi(Task* task){
    ui->scrollarea_tasks->widget()->layout()->removeWidget(task);
}
