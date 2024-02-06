#include "headers/user.h"
#include <QFileDialog>

struct task_data{
    QString task_name;
    QString group_name;
    QDate creation_date;
    bool is_complete;
    QDate completion_date;
};

User::User(QString username, QVector<Task*> all_tasks, QVector<Group*> all_groups): username(username), all_tasks(all_tasks), all_groups(all_groups){}


QString User::getUsername(){
    return username;
}

QVector<Group*> User::getGroups(){
    return all_groups;
}

QVector<Task*> User::getTasks(){
    return all_tasks;
}

void User::setUsername(QString new_username){
    username = new_username;
}

void User::appendGroup(Group* new_group){
    all_groups.append(new_group);
}

void User::appendTask(Task* new_task){
    all_tasks.append(new_task);
}

void User::updateData(){
    QJsonArray groupsArray;
    QJsonArray tasksArray;
    for(int i = 0; i < all_groups.size(); i++){
        groupsArray.append(all_groups[i]->get_name());
    }
    for(int j = 0; j < all_tasks.size(); j++){
        QJsonObject current_task;
        current_task["task_name"] = all_tasks[j]->getName();
        current_task["group_name"] = all_tasks[j]->getGroup();
        current_task["creation_date"] = all_tasks[j]->getCreationDate().toString("dd.MMM.yyyy");
        current_task["is_complete"] = all_tasks[j]->isComplete();
        current_task["completion_date"] = all_tasks[j]->getCompletionDate().toString("dd.MMM.yyyy");

        tasksArray.append(current_task);
    }

    user_data["groups"] = groupsArray;
    user_data["tasks"] = tasksArray;
}

void User::createJson(QString username){
    //QJsonObject data;
    this->user_data = QJsonObject();
    user_data["username"] = username;
    updateData();
}

void User::writeJsonFile(QString file_name){
    QFileInfo fileInfo(file_name);
    QFile jsonFile(file_name);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    jsonFile.write(QJsonDocument(user_data).toJson(QJsonDocument::Indented));
    jsonFile.close();
}
