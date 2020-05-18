#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene> //предоставляет поверхность для управления большим числом графических 2D элементов
#include "pillaritem.h"
#include <QTimer>
#include <birditem.h>
#include "savesfile.h"

class Scene : public QGraphicsScene
{
    //The Q_OBJECT macro must appear in the private section of a class definition that declares
    //its own signals and slots or that uses other services provided by Qt's meta-object system.
    Q_OBJECT

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    Scene(QObject *parent = nullptr); //explict
    void addBird();
    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();

    void setScore(int value);
    void showGameOverGraphics();
    void currentLvl(int lvl);

private:
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();
    QTimer *pillarTimer;
    BirdItem * bird;
    bool gameOn;

    int score;
    int bestScore;
    savesFile *save;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;
};

#endif // SCENE_H
