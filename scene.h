#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene> //предоставляет поверхность для управления большим числом графических 2D элементов
#include "pillaritem.h"
#include <QTimer>
#include <fishitem.h>
#include "savesfile.h"
#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>

/** Подключаем библиотеку, отвечающую за использование WinAPI
 * Данная библиотека необходима для асинхронной проверки состояния клавиш
 * */
#include <windows.h>

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
    void addFish();
    void startGame();
    void restartGame();

    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();

    void setScore(int value);
    void setTopCounter();
    void setNullTopCounter();
    void showGameOverGraphics();
    void showReachedLvlGraphics();
    void currentLvl(int lvl);
    void hideReachedLvlGraphics();
    void stopSoundPointReached();
    void bestScoreAndLvlInit();


private:
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeFishAndPillarsInPlace();
    void addSound(QMediaPlayer * m_player, QMediaPlaylist * m_playlist, QString path);
    QTimer *pillarTimer;
    FishItem * fish;
    bool gameOn;

    int score;
    int scoreLeft, scoreRight;
    int lvl;
    int bestScore;
    savesFile *save;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsPixmapItem * lvlReachedPix;
    QGraphicsTextItem * scoreTextItem;

    QGraphicsPixmapItem * topCounterRight;
    QGraphicsPixmapItem * topCounterLeft;

    QMediaPlayer * m_player;        // Аудио плеер
    QMediaPlaylist * m_playlist;    // Плейлист

    QMediaPlayer * mPlayerPoint;        // Аудио плеер
    QMediaPlaylist * mPlayListPoint;    // Плейлист

    QMediaPlayer * mPlayerHit;        // Аудио плеер
    QMediaPlaylist * mPlayListHit;    // Плейлист
};

#endif // SCENE_H
