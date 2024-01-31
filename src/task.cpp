#include "headers/task.h"
#include "ui_task.h"
#include <QDebug>
Task::Task(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    this->setData("New task", "Unsorted", QDate::currentDate(), false, QDate::currentDate());
}

//GETTERS
QString Task::getName(){
    return task_name;
}

QString Task::getGroup(){
    return task_group;
}

QDate Task::getCreationDate(){
    return creation_date;
}


bool Task::isComplete(){
    return is_complete;
}

QDate Task::getCompletionDate(){
    return completion_date;
}


//SETTERS
void Task::setName(QString name){
    this->task_name = name;
}

void Task::setGroup(QString group){
    this->task_group = group;
}

void Task::setCreationDate(QDate creation_date){
    this->creation_date = creation_date;
}

void Task::setStatus(bool is_complete){
    this->is_complete = is_complete;
}

void Task::setCompletionDate(QDate completion_date){
    this->completion_date = completion_date;
}

void Task::enableCompleted(){
    this->ui->label_TaskCompleted->show();
}

void Task::disableCompleted(){
    this->ui->label_TaskCompleted->hide();
}

void Task::updateUI(){
    this->ui->label_taskName->setText(this->getName());
    this->ui->label_TaskDate->setText("Created:" + this->getCreationDate().toString("dd.MMM.yyyy"));
    this->ui->label_TaskCompleted->setText("Done:" + this->getCompletionDate().toString("dd.MMM.yyyy"));
    if(this->isComplete() == true){
        this->enableCompleted();
    }else{
        this->disableCompleted();
    }
}


void Task::setData(QString name, QString group, QDate creation_date, bool is_complete, QDate completion_date){
    this->setName(name);
    this->setGroup(group);
    this->setCreationDate(creation_date);
    this->setStatus(is_complete);
    if(this->isComplete()){
        this->setCompletionDate(completion_date);
    }
    this->setStatus(is_complete);
    updateUI();
}

void Task::changeToUndoneButton(){
    ui->button_Complete->setText("Undone");

}

void Task::changeToDoneButton(){
    ui->button_Complete->setText("Done");

}

Task::~Task()
{
    delete ui;
}

void Task::on_button_Edit_clicked()
{
    emit taskEdit(this);
}


void Task::on_button_Delete_clicked()
{
    emit taskDelete(this);
}


void Task::on_button_Complete_clicked()
{
    if(ui->button_Complete->text() == "Done"){
        changeToUndoneButton();
        this->setStatus(true);
        this->setCompletionDate(QDate::currentDate());
        updateUI();
        emit taskComplete(this);
    }
    else if(ui->button_Complete->text() == "Undone"){
        changeToDoneButton();
        this->setStatus(false);
        updateUI();
        emit taskUncomplete(this);
    }

}

