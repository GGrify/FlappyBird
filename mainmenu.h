#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "widget.h"
#include "scene.h"
#include "score.h"

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
     Score *score;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::mainMenu *ui;

    Scene *scene;
    savesFile *save;

};

#endif // MAINMENU_H
