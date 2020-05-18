#include "birditem.h"
#include <QTimer>
#include <QTransform>
#include <QGraphicsScene>

BirdItem::BirdItem(QPixmap pixmap) :
    wingPosition(WingPosition::Up),
    wingDirection(0)
{

    setPixmap(pixmap);

    QTimer * birdWingTimer = new QTimer(this);
    connect(birdWingTimer, &QTimer::timeout, [=]() {
        updatePixmap();
    });

    birdWingTimer->start(80); //asdasd
    groundPosition = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
}

//реалізація функції підняття пташки вгору
void BirdItem::shootUp()
{
    //зупиняємо анімації
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y(); //визиваєм геттер y, щоб получити координати пташки(тєкущі)
    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8); // можна легко настроїти, замість 8 щось інше
    yAnimation->setEasingCurve(QEasingCurve::OutQuad); //можна помвняти анімацію
    yAnimation->setDuration(285); //і тут поміняти число

    connect(yAnimation, &QPropertyAnimation::finished, [=]() {
        fallToGroundIfNecessary();
    });

    yAnimation->start();
    rotateTo(-20, 200, QEasingCurve::OutCubic);

}

void BirdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);
}

qreal BirdItem::rotation() const
{
    return m_rotation;
}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF c = this->boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void BirdItem::setY(qreal y)
{
    this->moveBy(0, y-m_y);
    m_y = y;
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
        rotationAnimation->setStartValue(rotation());
        rotationAnimation->setEndValue(end);
        rotationAnimation->setEasingCurve(curve);
        rotationAnimation->setDuration(duration);

        rotationAnimation->start();
}

void BirdItem::fallToGroundIfNecessary()
{
    if(y() < groundPosition) {
        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90,1200,QEasingCurve::InQuad);
    }
}

void BirdItem::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}

void BirdItem::updatePixmap()
{

    if(wingPosition == WingPosition::Middle) {

        if(wingDirection) {
            //Up
            setPixmap(QPixmap(":/images/yellowbird-upflap.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        } else {
            //down
            setPixmap(QPixmap(":/images/yellowbird-downflap.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }

    } else {
        setPixmap(QPixmap(":/images/yellowbird-midflap.png"));
        wingPosition = WingPosition::Middle;
    }

}
