#ifndef PILLARITEM_H
#define PILLARITEM_H

//Класс QGraphicsItemGroup представляет группу элементов в качестве одного целого
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

#include "scene.h"
#include "savesfile.h"

#include <QGraphicsScene>
#include "fishitem.h"

class PillarItem : public QObject,  public QGraphicsItemGroup
{
    Q_OBJECT
    //встановити геттер і сеттер для свойства
    //ми наследуем QObject щоб юзати Q_PROPERTY
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem(); //удаляєм наші блоки, які пташка пройшла, щоб вони не займали пам'ять
    qreal x() const;

    void freezeInPlace();;

signals:
    void collideFail();

public slots:

    void setX(qreal x);

private:
    QGraphicsPixmapItem * topPillar; //верхня палка
    QGraphicsPixmapItem * bottomPillar; //нижня палка
    QPropertyAnimation * xAnimation; // анімація по осі x
    savesFile *save;

    bool collidesWithFish();

    int yPos;
    int lvlPillar;
    int pillarGap;
    int pillarSpeed;
    qreal m_x;
    bool pastFish;

};

#endif // PILLARITEM_H
