#include "maintasks.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainTasks w;
    w.show();
    return a.exec();
}
