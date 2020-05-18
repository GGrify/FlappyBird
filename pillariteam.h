#ifndef PILLARITEAM_H
#define PILLARITEAM_H

//Класс QGraphicsItemGroup представляет группу элементов в качестве одного целого
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class PillarIteam : public QObject,  public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit PillarIteam();

signals:

private:
    QGraphicsPixmapItem * topPillar; //верхня палка
    QGraphicsPixmapItem * bottomPillar; //нижня палка
};

#endif // PILLARITEAM_H
