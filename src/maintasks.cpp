#include "headers/maintasks.h"
#include "ui_maintasks.h"
#include "headers/task.h"
#include "headers/taskdialog.h"
#include "headers/group.h"
#include "user.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QStackedWidget>
#include <QJsonDocument>
#include <QJsonObject>

MainTasks::MainTasks(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainTasks)
{
    ui->setupUi(this);

    stack = new QStackedWidget;
    ui->scrollarea_main->setWidget(stack);

    //SETTING UP GROUPPED CONTAINER
    QWidget* container_groupped = new QWidget();
    QHBoxLayout *groups_layout = new QHBoxLayout(container_groupped);
    groups_layout->setSizeConstraint(QLayout::SetMinimumSize);

    QPushButton* add_group = new QPushButton(container_groupped);
    add_group->setText("Add group");
    add_group->setFixedSize(QSize(300, 30));
    groups_layout->addWidget(add_group);
    connect(add_group, &QPushButton::clicked, this, &MainTasks::groupAdd);
    stack->addWidget(container_groupped);

    //SETTING UP UNGROUPPED CONTAINER
    QWidget* container_ungroupped = new QWidget();
    QVBoxLayout *tasks_layout = new QVBoxLayout(container_ungroupped);
    tasks_layout->setSizeConstraint(QLayout::SetMinimumSize);
    tasks_layout->setAlignment(Qt::AlignCenter);

    QPushButton* add_task = new QPushButton(container_ungroupped);
    add_task->setText("Add task");
    add_task->setFixedSize(QSize(300, 30));
    tasks_layout->addWidget(add_task);
    connect(add_task, &QPushButton::clicked, this, &MainTasks::taskAddFromUngroupped);
    stack->addWidget(container_ungroupped);


    //SETTING UP COMPLETE TASKS CONTAINER
    QWidget* container_complete = new QWidget();
    QVBoxLayout *complete_layout = new QVBoxLayout(container_complete);
    complete_layout->setSizeConstraint(QLayout::SetMinimumSize);
    complete_layout->setAlignment(Qt::AlignCenter);
    stack->addWidget(container_complete);


    // Unsorted tasks
    if(getGroupIndex("Unsorted") == -1){
        Group* unsorted_group = new Group;
        unsorted_group->setGroupName("Unsorted");
        all_groups.push_front(unsorted_group);
    }


    //Adding groups and tasks to groupped ui
    setUpGroupped();
    for(int i = 0; i < all_groups.size(); i++){
        connect(all_groups[i], &Group::creatingTask, this, &MainTasks::taskAddFromGroupped);
        addGroupToUi(all_groups[i]);
    }
    for(int i = 0; i < all_tasks.size(); i++){
        addTaskToGroupUi(all_tasks[i]);
    }



    QJsonObject save_data{
        {"username", ""},
        {"groups", {}},
        {"tasks", {}}
    };

}

MainTasks::~MainTasks()
{
    delete ui;
}


void MainTasks::setUpGroupped(){
    stack->setCurrentIndex(0);
    for(int i = 0; i < all_tasks.size(); i++){
        if(all_tasks[i]->isComplete() != true){
            addTaskToGroupUi(all_tasks[i]);
        }
    }
}

void MainTasks::setUpUngroupped(){
    stack->setCurrentIndex(1);
    for(int i = 0; i < all_tasks.size(); i++){
        if(all_tasks[i]->isComplete() != true){
            addTaskToUngrouppedUi(all_tasks[i]);
        }
    }
}

void MainTasks::setUpComplete()
{
    stack->setCurrentIndex(2);
    if(stack->currentWidget()->layout()->count() == 0){
        QMessageBox::information(this, "No tasks", "You haven't completed any tasks yet.");
    }
}

void MainTasks::addGroupToUi(Group* group){
    int elements = stack->currentWidget()->layout()->count();
    QLayoutItem* add_group = stack->currentWidget()->layout()->itemAt(elements-1);
    stack->currentWidget()->layout()->removeItem(add_group);

    stack->currentWidget()->layout()->addWidget(group);
    stack->currentWidget()->layout()->addItem(add_group);
}

void MainTasks::addTaskToGroupUi(Task* task){
    for(int i = 0; i < all_groups.size(); i++){
        if(all_groups[i]->get_name() == task->getGroup()){
            if(task->isComplete()){
                stack->widget(2)->layout()->addWidget(task);
                task->changeToUndoneButton();
                return;
            }
                all_groups[i]->addTaskToUi(task);
            return;
        }
    }
}

void MainTasks::addTaskToUngrouppedUi(Task* task){
    if(task->isComplete()){
        stack->widget(2)->layout()->addWidget(task);
        task->changeToUndoneButton();
        return;
    }
    int elements = stack->currentWidget()->layout()->count();
    QLayoutItem* add_task = stack->currentWidget()->layout()->itemAt(elements-1);
    stack->currentWidget()->layout()->removeItem(add_task);

    stack->currentWidget()->layout()->addWidget(task);
    stack->currentWidget()->layout()->addItem(add_task);
}

void MainTasks::groupAdd(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new group"),
                                             tr("Group name:"), QLineEdit::Normal,
                                             tr("New group"), &ok);
    if (ok && !text.isEmpty()){
        //leave it here
        Group* group = new Group();
        connect(group, &Group::creatingTask, this, &MainTasks::taskAddFromGroupped);
        group->setGroupName(text);
        all_groups.append(group);
        addGroupToUi(group);
    }
}

void MainTasks::taskCreate(TaskInfo task_info){
    Task* new_task = new Task;
    new_task->setData(task_info.task_name, all_groups[task_info.task_group]->get_name(), task_info.creation_date, task_info.is_complete, task_info.complete_date);
    connect(new_task, &Task::taskEdit, this, &MainTasks::taskEdit);
    connect(new_task, &Task::taskDelete, this, &MainTasks::taskDelete);
    connect(new_task, &Task::taskComplete, this, &MainTasks::taskComplete);
    connect(new_task, &Task::taskUncomplete, this, &MainTasks::taskUncomplete);
    all_tasks.append(new_task);
}

void MainTasks::taskAddFromGroupped(Group* group){
    //Setting up Task dialog
    TaskDialog* get_task_data = new TaskDialog;
    get_task_data->set_groups(all_groups);
    get_task_data->set_dialog_data("", all_groups.indexOf(group), QDate::currentDate(), false, QDate::currentDate());
    get_task_data->lock_group();

    if(get_task_data->exec() == QDialog::Accepted){
        TaskInfo task_info = get_task_data->get_values();
        taskCreate(task_info);
        if(all_tasks.last()->isComplete()){
            stack->widget(2)->layout()->addWidget(all_tasks.last());
            all_tasks.last()->changeToUndoneButton();
            return;
        }
        all_groups[task_info.task_group]->addTaskToUi(all_tasks.last());
    }
}

void MainTasks::taskAddFromUngroupped(){
    TaskDialog* get_task_data = new TaskDialog;
    get_task_data->set_groups(all_groups);
    get_task_data->set_dialog_data("", 0, QDate::currentDate(), false, QDate::currentDate());

    if(get_task_data->exec() == QDialog::Accepted){
        TaskInfo task_info = get_task_data->get_values();
        taskCreate(task_info);
        addTaskToUngrouppedUi(all_tasks.last());
    }
}

void MainTasks::taskEdit(Task* task){
    TaskDialog* get_task_data = new TaskDialog;
    int group_index = 0;
    for(int i = 0; i < all_groups.size(); i++){
        if(task->getGroup() == all_groups[i]->get_name()){
            group_index = i;
            break;
        }
    }
    get_task_data->set_groups(all_groups);
    get_task_data->set_dialog_data(task->getName(), group_index, task->getCreationDate(), task->isComplete(), task->getCompletionDate());
    if(get_task_data->exec() == QDialog::Accepted){
        QString old_group = task->getGroup();
        TaskInfo task_info = get_task_data->get_values();
        task->setData(task_info.task_name, all_groups[task_info.task_group]->get_name(), task_info.creation_date, task_info.is_complete, task_info.complete_date);
        if(task->getGroup() != old_group){
            all_groups[task_info.task_group]->addTaskToUi(task);
        }
    }
}

void MainTasks::taskDelete(Task* task){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Deleting task","Do you want to delete this task?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        all_tasks.removeOne(task);
        int good_group = 0;
        for(int i = 0; i < all_groups.size(); i++){
            if(all_groups[i]->get_name() == task->getGroup()){
                good_group = i;
                break;
            }
        }
        all_groups[good_group]->removeTaskFromUi(task);
        task->setParent(0);
        delete task;
    }
    else
    {
        return;
    }

}

void MainTasks::taskComplete(Task* task){
    stack->widget(2)->layout()->addWidget(task);
}

int MainTasks::getGroupIndex(QString group_name){
    for(int i = 0; i < all_groups.size(); i++){
        if(all_groups[i]->get_name() == group_name){
            return i;
        }
    }
    return -1;
}

void MainTasks::taskUncomplete(Task* task){
    addTaskToGroupUi(task);
}

void MainTasks::on_actionView_unsorted_triggered()
{
    setUpUngroupped();
}


void MainTasks::on_actionSort_by_group_triggered()
{
    setUpGroupped();
}


void MainTasks::on_actionView_completed_tasks_triggered()
{
    setUpComplete();
}


void MainTasks::on_actionNew_user_triggered()
{
    User* current_user = new User("Current", all_tasks, all_groups);
    current_user->updateData();
    current_user->writeJsonFile("current_user");
}

