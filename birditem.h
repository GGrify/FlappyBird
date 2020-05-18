#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class BirdItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    BirdItem(QPixmap pixmap);

    void shootUp();
    void startFlying();

    qreal rotation() const;

    qreal y() const;

public slots:
    void setRotation(qreal rotation);

    void setY(qreal y);
    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);

    void fallToGroundIfNecessary();

    void freezeInPlace();

private:
    enum WingPosition {
        Up,
        Middle,
        Down
    };
    void updatePixmap();
    WingPosition wingPosition;
    bool wingDirection; //0 : down, 1: up
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    qreal groundPosition;
};

#endif // BIRDITEM_H
