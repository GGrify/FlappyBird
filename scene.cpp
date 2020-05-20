#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "QDebug"
#include <QDir>
#include <QUrl>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false), score(0), scoreLeft(1),
    scoreRight(0)
{
    setUpPillarTimer();

    save = new savesFile();
    bestScore = save->getFileScore();
    lvl = save->readFileLvl();

    mPlayerPoint = new QMediaPlayer(this);          // Инициализация плеера
    mPlayListPoint = new QMediaPlaylist(mPlayerPoint);  // Инициализация плейлиста

    mPlayerHit = new QMediaPlayer(this);          // Инициализация плеера
    mPlayListHit = new QMediaPlaylist(mPlayerPoint);  // Инициализация плейлиста

    addSound(mPlayerHit, mPlayListHit, "qrc:/sounds/sfx_hit.mp3");

    mPlayerPoint->setPlaylist(mPlayListPoint);      // Устанавливаем плейлист в плеер
    mPlayListPoint->addMedia(QUrl("qrc:/sounds/sfx_point.mp3")); // Добавляем аудио в плейлист
    mPlayListPoint->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);   // Проигрываем трек один раз


}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/images/yellowbird-upflap.png"));
    addItem(bird);
}

void Scene::startGame()
{

    if(save->readFileLvl() == 0) {
        hideGameOverGraphics();
        showReachedLvlGraphics();
        return;
    }

    //Bird
    this->setNullTopCounter();
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
    m_player = new QMediaPlayer(this);          // Инициализация плеера
    m_playlist = new QMediaPlaylist(m_player);  // Инициализация плейлиста

    addSound(m_player, m_playlist, "qrc:/sounds/sfx_wing.mp3");

    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=]() {

        PillarItem *pillarItem = new PillarItem();
        //ВИРУБАЭМ ЫГРУ
        connect(pillarItem, &PillarItem::collideFail, [=]() {
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            mPlayerHit->play();
            showGameOverGraphics();
        });

        addItem(pillarItem);

    });

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

void Scene::addSound(QMediaPlayer *m_player, QMediaPlaylist *m_playlist, QString path)
{
    m_player->setPlaylist(m_playlist);      // Устанавливаем плейлист в плеер
    m_playlist->addMedia(QUrl(path)); // Добавляем аудио в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);   // Проигрываем трек один раз
}

void Scene::setScore(int value)
{
    score = value;
    scoreRight = value;
    scoreLeft = 1;
}

void Scene::setTopCounter()
{
    qDebug() << "MUST WORK HERE!!!!!!!!!";
    topCounterRight = new QGraphicsPixmapItem(QPixmap(":/images/0.png"));
    topCounterLeft = new QGraphicsPixmapItem(QPixmap(""));
    topCounterRight->setPos(QPointF(0, 0));
    topCounterLeft->setZValue(1);
    topCounterRight->setZValue(1);
    this->addItem(topCounterRight);
    this->addItem(topCounterLeft);

    topCounterRight->setPos(QPointF(15, -300) - QPointF(topCounterRight->boundingRect().width() / 2, 0));
    topCounterLeft->setPos(QPointF(-15, -300) - QPointF(topCounterRight->boundingRect().width() / 2, 0));
}

void Scene::setNullTopCounter()
{
    topCounterRight->setPixmap(QPixmap(":/images/0.png"));
    topCounterLeft->setPixmap(QPixmap(""));
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
    mPlayerPoint->play();
    score++;
    scoreRight++;

    QString pathCountsRight = ":/images/" + QString::number(scoreRight) + ".png";

    if(score < 10) topCounterRight->setPixmap(QPixmap(pathCountsRight));
    if(score >= 10 && score <= 99) {
        QString pathCountsLeft = ":/images/" + QString::number(scoreLeft) + ".png";
        if((score % 10) == 0) {
            scoreLeft++;
            scoreRight = 0;
            pathCountsRight = ":/images/" + QString::number(scoreRight) + ".png";
            topCounterLeft->setPixmap(QPixmap(pathCountsLeft));
        }
        topCounterRight->setPixmap(QPixmap(pathCountsRight));
    }

    if(score > bestScore) {
        bestScore = score;
        save->writeFileScore(bestScore);
    }


    if((bestScore == lvlTwoScore) && (lvl == 1)) {
        pillarTimer->stop();
        freezeBirdAndPillarsInPlace();
        setGameOn(false);
        showReachedLvlGraphics();
        setNullTopCounter();
        lvl = 2;
    }

    if((bestScore == lastLvlScore) && (lvl == 2)) {
        pillarTimer->stop();
        freezeBirdAndPillarsInPlace();
        setGameOn(false);
        showReachedLvlGraphics();
        setNullTopCounter();
        lvl = 3;
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

void Scene::showReachedLvlGraphics()
{
    switch (lvl) {
    case 1:
        lvlReachedPix = new QGraphicsPixmapItem(QPixmap(":/images/reached_lvl_2.png"));
        addItem(lvlReachedPix);
        lvlReachedPix->setPos(QPointF(0, 0) - QPointF(lvlReachedPix->boundingRect().width() / 2,
                                                lvlReachedPix->boundingRect().height() / 2));
        break;
    case 2:
    case 0:
        lvlReachedPix = new QGraphicsPixmapItem(QPixmap(":/images/reached_last_lvl.png"));
        addItem(lvlReachedPix);
        lvlReachedPix->setPos(QPointF(0, 0) - QPointF(lvlReachedPix->boundingRect().width() / 2,
                                                lvlReachedPix->boundingRect().height() / 2));
        break;
    }

}

void Scene::currentLvl(int lvl)
{
    switch (lvl) {
    case 1:
        lvl = 1;
        break;
    case 2:
        lvl = 2;
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

void Scene::hideReachedLvlGraphics()
{
    if(lvlReachedPix) {
        removeItem(lvlReachedPix);
        delete lvlReachedPix;
        lvlReachedPix = nullptr;
    }

}

void Scene::bestScoreAndLvlInit()
{
    bestScore = save->getFileScore();
    lvl = save->readFileLvl();
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
        if(gameOn) {
            m_player->stop();
            bird->shootUp();
            m_player->play();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(gameOn) {
            m_player->stop();
            bird->shootUp();
            m_player->play();
        }
    }
    QGraphicsScene::mousePressEvent(event);

}
