#include "maintasks.h"
#include "ui_maintasks.h"
#include "task.h"
#include <group.h>

#include <QScrollArea>
#include<QVBoxLayout>
#include <QDebug>
MainTasks::MainTasks(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTasks)
{
    ui->setupUi(this);


    QWidget *container = new QWidget(this);
    QHBoxLayout *groups_layout = new QHBoxLayout(container);
    groups_layout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->groupLayout->setWidget(container);
    ui->groupLayout->setWidgetResizable(true);
    QPushButton* add_group = new QPushButton();
    add_group->setText("Add group");
    add_group->setFixedSize(QSize(300, 30));
    groups_layout->addWidget(add_group);
    connect(add_group, &QPushButton::clicked, this, &MainTasks::groupAdd);
}

MainTasks::~MainTasks()
{
    delete ui;
}


void MainTasks::on_button_test_addGroup_clicked()
{

}

void MainTasks::groupAdd(){
    int elements = ui->groupLayout->widget()->layout()->count();
    QLayoutItem* add_group = ui->groupLayout->widget()->layout()->itemAt(elements-1);
    ui->groupLayout->widget()->layout()->removeItem(add_group);

    Group* group = new Group();
    ui->groupLayout->widget()->layout()->addWidget(group);
    ui->groupLayout->widget()->layout()->addItem(add_group);
}
