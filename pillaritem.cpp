#include "pillaritem.h"
#include <QRandomGenerator> //класс для генерації випадкових чисел
#include <QDebug>


PillarItem::PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png"))),
    pastFish(false)
{
    addToGroup(topPillar); //методи класу QGraphicsItemGroup, передаємо їм наші pillars щоб добавити в групу
    addToGroup(bottomPillar);

    save = new savesFile();

    lvlPillar = save->readFileLvl();

    switch (lvlPillar) {
        case 1:
            pillarGap = 80;
            pillarSpeed = 1500;
        break;
        case 2:
            pillarGap = 70;
            pillarSpeed = 1600;
        break;
    }

    topPillar->setPos(QPointF(0, 0) - QPointF(topPillar->boundingRect().width() / 2,
                                              topPillar->boundingRect().height() + pillarGap)); //поміняти при зміні lvl-а
    bottomPillar->setPos(QPointF(0, 0) + QPointF(-bottomPillar->boundingRect().width() / 2,
                                                 60));

    yPos = QRandomGenerator::global()->bounded(150); //задаємо yPosition наших pillars (
    int xRandomizer = QRandomGenerator::global()->bounded(2); //200

    setPos(QPointF(0,0) + QPointF(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this); //x имя свойста, яке ми будемо линковать через Q_PROPERY
    xAnimation->setStartValue(260 + 240);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(pillarSpeed);

    connect(xAnimation, &QPropertyAnimation::finished, [=]() { //краткая форма записи анонимных функторов
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();

}

PillarItem::~PillarItem()
{
    qDebug() << "Deleting Pillar";
    delete topPillar;
    delete bottomPillar;
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();
}


void PillarItem::setX(qreal x)
{
    m_x = x;

    if(x < 0 && !pastFish) {
        pastFish = true;
        QGraphicsScene * mScene = scene(); //повертає поточну сцену item-а, нашого pillar-а
        Scene *myScene = dynamic_cast<Scene *>(mScene); //потрібно якось визвати incrementScore
        if(myScene) myScene->incrementScore();
    }

    if(collidesWithFish()) emit collideFail(); //якщо зіткнення відбулось то спрацьовує сигнал, який реалізовано в сцені
    setPos(QPoint(0,0) + QPointF(x, yPos));
}

bool PillarItem::collidesWithFish()
{
    //Метод collidingItems Возвращает список элементов, которые сталкиваются с этим элементом.
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems(); //QList - Он хранит список значений и обеспечивает быстрый доступ на основе индекса, а также быстрые вставки и удаления.
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem * item, collidingItems) {
        FishItem * fishItem = dynamic_cast<FishItem*>(item);
        if(fishItem) return true; //спрацьовує при зіткненні
    }
    return false;
}
