#include "pillaritem.h"
#include <QRandomGenerator> //класс для генерації випадкових чисел
#include <QDebug>
#include <QGraphicsScene>
#include "birditem.h"
#include "scene.h"
#include "savesfile.h"

PillarItem::PillarItem() :
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pipe-green.png"))),
    pastBird(false)
{

    //методи класу QGraphicsItemGroup, передаэмо їм наші pillars щоб добавити в групу
    addToGroup(topPillar);
    addToGroup(bottomPillar);

    savesFile *save = new savesFile();

    lvlPillar = save->readFileLvl();

    switch (lvlPillar) {
        case 1:
            pillarGap = 80;
            pillarSpeed = 1600;
        break;
        case 2:
            pillarGap = 60;
            pillarSpeed = 1250;
        break;
    }

    topPillar->setPos(QPointF(0, 0) - QPointF(topPillar->boundingRect().width() / 2,
                                              topPillar->boundingRect().height() + pillarGap)); //поміняти при зміні lvl-а
    bottomPillar->setPos(QPointF(0, 0) + QPointF(-bottomPillar->boundingRect().width() / 2,
                                                 60));

    yPos = QRandomGenerator::global()->bounded(150); //задаємо yPosition наших pillars (
    int xRandomizer = QRandomGenerator::global()->bounded(200); //200

    setPos(QPointF(0,0) + QPointF(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x", this); //x имя свойста, яке ми будемо линковать через Q_PROPERY
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(pillarSpeed);

    connect(xAnimation, &QPropertyAnimation::finished, [=]() {
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
   // qDebug() << "Pillar position: " << x;
    m_x = x;

    if(x < 0 && !pastBird) {
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene *myScene = dynamic_cast<Scene *>(mScene);
        if(myScene)
            myScene->incrementScore();
    }

    if(collidesWithBird()) {
        emit collideFail();
    }
    setPos(QPoint(0,0) + QPointF(x, yPos));
}

bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());

    foreach(QGraphicsItem * item, collidingItems) {
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem) {
            return true;
        }
    }
    return false;
}
