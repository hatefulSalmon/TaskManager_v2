#ifndef USER_H
#define USER_H
#include <QtCore>
#include <QVector>
#include "headers/group.h"
#include "headers/task.h"

class User
{
public:
    User(QString username, QVector<Task*> all_tasks, QVector<Group*> all_groups);

    QString getUsername();

    QVector<Group*> getGroups();
    QVector<Task*> getTasks();

    void setUsername(QString new_username);

    void appendGroup(Group* new_group);

    void appendTask(Task* new_task);



    //JSON interface

    void createJson(QString username);
    void writeJsonFile(QString file_name);
    void updateData();
    //readFromJson()

private:
    QString username;
    QVector<Task*> all_tasks;
    QVector<Group*> all_groups;

    QJsonObject user_data;
};

#endif // USER_H
