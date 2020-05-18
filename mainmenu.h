#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "widget.h"
#include "scene.h"

namespace Ui {
class mainMenu;
}

class mainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();
     Widget *game;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mainMenu *ui;

    Scene *scene;
};

#endif // MAINMENU_H
