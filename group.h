#ifndef GROUP_H
#define GROUP_H

#include <QWidget>

namespace Ui {
class Group;
}

class Group : public QWidget
{
    Q_OBJECT

public:
    explicit Group(QWidget *parent = nullptr);
    ~Group();

private slots:
    void on_button_addTask_clicked();

private:
    Ui::Group *ui;
};

#endif // GROUP_H
