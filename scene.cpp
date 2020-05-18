#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "QDebug"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0)
{
    setUpPillarTimer();

    save = new savesFile();
    bestScore = save->getFileScore();

}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/images/yellowbird-upflap.png"));
    addItem(bird);
}

void Scene::startGame()
{

    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive()) {
        qDebug() << "Hello wordl!";
        cleanPillars();
        setGameOn(true);
        //СЮДА
        setScore(0);
        hideGameOverGraphics();
        pillarTimer->start(1000);
    }
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=]() {

        PillarItem *pillarItem = new PillarItem();
        //ВИРУБАЭМ ЫГРУ
        connect(pillarItem, &PillarItem::collideFail, [=]() {
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });

        addItem(pillarItem);

    });

    // pillarTimer->start(1000); начать добавлять pillars на сцену

}

void Scene::freezeBirdAndPillarsInPlace()
{
    //Freeze bird
    bird->freezeInPlace();

    //Freeze pillars
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems) {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar) {
            pillar->freezeInPlace();
        }
    }
}

void Scene::setScore(int value)
{
    score = value;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    score++;
    if(score > bestScore) {
        bestScore = score;
        save->writeFileScore(bestScore);
    }

    if(bestScore == 10) {
        pillarTimer->stop();
        freezeBirdAndPillarsInPlace();
        setGameOn(false);
        showGameOverGraphics();
        save->writeFileLvl("Lvl: 2");
    }

    qDebug() << "Score : " << score << "Best score : " << bestScore;
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/images/gameover.png"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0, 0) - QPointF(gameOverPix->boundingRect().width() / 2,
                                                gameOverPix->boundingRect().height() / 2));


    scoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> Score : " + QString::number(score) + " </p>"
                                        + "<p> Best Score : " + QString::number(bestScore) + "</p>";

    QFont mFont("Consolas", 30, QFont::Bold);
    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::yellow);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0, 0) - QPointF(scoreTextItem->boundingRect().width() / 2,
                                                  -gameOverPix->boundingRect().height() / 2));
}

void Scene::currentLvl(int lvl)
{
    switch (lvl) {
    case 1:

    break;
    }
}

void Scene::hideGameOverGraphics()
{

    if(gameOverPix) {
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }

    if(scoreTextItem) {
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }

}

void Scene::cleanPillars()
{

    //Freeze pillars
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems) {
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar) {
            removeItem(pillar);
            delete pillar;
        }
    }

}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space) {
        if(gameOn)
            bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(gameOn)
            bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);

}
