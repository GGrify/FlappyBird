#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget> //Класс QWidget является базовым для всех объектов пользовательского интерфейса
#include <QMouseEvent>
#include "scene.h"
#include "savesfile.h"
#include <QKeyEvent>

namespace Ui { class Widget; }

class Widget : public QWidget //створили клас Widget, який наслідує від класу QWidget - який є основою для вілжетів
{
    Q_OBJECT // // этот макрос должен включаться в классы, которые объявляют свои собственные сигналы и слоты

public:
    //Значение по умолчанию nullptr, то есть нулевой указатель. То есть мы подразумеваем, что по умолчанию у нашего виджета, нет виджет-родителя.
    //Следовательно наш виджет, по умолчанию, будет виджетом верхнего уровня. (Если совсем грубо говоря - независимым окном)
    Widget(QWidget *parent = nullptr);
    void showWidget();
    ~Widget();

signals:
    void firstWindow();
private slots:
    void getItemImagesOnLvl();
    void on_startAgain_clicked();
    void on_backMenu_clicked();
    void continueGame();

    void on_restartGame_clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;

private:
    Scene * scene;
    savesFile *save;
    QString lvlPhrasePath;
    QString backgroundPhrasePath;
    QGraphicsPixmapItem *pixItem;
    QGraphicsPixmapItem *lvlItem;

};
#endif // WIDGET_H
