#include "widget.h"
#include "./ui_widget.h"
//Класс QGraphicsPixmapItem предоставляет элемент растрового изображения, который вы можете добавить на QGraphicsScene
#include <QGraphicsPixmapItem>
#include "pillaritem.h"
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600); // -250 -300 500 600

//    scene->addLine(-400, 0, 400, 0, QPen(Qt::blue));
//    scene->addLine(0, -400, 0, 400, QPen(Qt::blue));

    save = new savesFile();

    getItemImagesOnLvl();

    pixItem = new QGraphicsPixmapItem(QPixmap(backgroundPhrasePath));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(-262.5,-312.5));

    lvlItem = new QGraphicsPixmapItem(QPixmap(lvlPhrasePath));
    scene->addItem(lvlItem);
    lvlItem->setPos(QPointF(-250,-300));
    scene->currentLvl(save->readFileLvl());

    //Устанавливает текущую сцену равной scene. Если сцена scene уже отображается этом видом, то эта функция ничего не делает.
    ui->graphicsView->setScene(scene);

    scene->addBird();
    scene->showGameOverGraphics();
}

void Widget::showWidget()
{
    scene->startGame();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    this->close();
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void Widget::getItemImagesOnLvl()
{
    switch(save->readFileLvl()) {
    case 1:
        lvlPhrasePath = ":/images/lvl_1.png";
        backgroundPhrasePath = ":/images/BG_2.png";
        break;
    case 2:
        lvlPhrasePath = ":/images/lvl_2.png";
        backgroundPhrasePath = ":/images/BG_3.png";
        break;
    }
}

void Widget::on_pushButton_2_clicked()
{
    getItemImagesOnLvl();
    pixItem->setPixmap(QPixmap(backgroundPhrasePath));
    lvlItem->setPixmap(QPixmap(lvlPhrasePath));
    scene->currentLvl(save->readFileLvl());
    scene->startGame();
}
