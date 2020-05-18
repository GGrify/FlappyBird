#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);

    game = new Widget();
    connect(game, &Widget::firstWindow, this, &Widget::show);
}

mainMenu::~mainMenu()
{
    delete ui;
}


void mainMenu::on_pushButton_clicked()
{

    game->show();  // Показываем второе окно
    game->showWidget();
    this->close();    // Закрываем основное окно
}

void mainMenu::on_pushButton_2_clicked()
{
    this->close();
}
