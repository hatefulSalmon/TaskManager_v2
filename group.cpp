#include "group.h"
#include "ui_group.h"
#include "task.h"
#include <QVBoxLayout>
Group::Group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Group)
{
    ui->setupUi(this);
    QWidget* container = new QWidget(this);
    QVBoxLayout* tasksLayout = new QVBoxLayout(container);
    ui->scrollarea_tasks->setWidget(container);

}

Group::~Group()
{
    delete ui;
}

void Group::on_button_addTask_clicked()
{
    Task* task = new Task();
    ui->scrollarea_tasks->widget()->layout()->addWidget(task);
    //ui->tasksLayout->addWidget(task);
    //ui->groupLayout->widget()->layout()->addWidget(task);
}

