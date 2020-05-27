#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{

    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );

    ui->setupUi(this);


    game = new Widget();
    save = new savesFile();
    score = new Score();
    score->setWindowTitle("Swimmy Fish - Score");
    connect(game, &Widget::firstWindow, this, &Widget::show);
    connect(score, &Score::secondWindow, this, &Widget::show);
}

mainMenu::~mainMenu()
{
    delete ui;
}


void mainMenu::on_pushButton_clicked() //start gane
{
    game->setWindowTitle("Swimmy Fish");
    game->setWindowIcon(QIcon(":/images/yellowbird-midflap.png"));
    game->show();  // Показываем второе окно
    game->showWidget();
    this->close();    // Закрываем основное окно
}

void mainMenu::on_pushButton_2_clicked()
{
    this->close();
}

void mainMenu::on_pushButton_3_clicked()
{

    score->show();
    score->writeScoreOnLabel();
    if(lastLvlScore == save->getFileScore()) {
        score->writeRewardLabel();
    }
    this->close();
}
