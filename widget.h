#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget> //Класс QWidget является базовым для всех объектов пользовательского интерфейса
#include "scene.h"
#include "savesfile.h"

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

private:
    Scene * scene;
};
#endif // WIDGET_H
