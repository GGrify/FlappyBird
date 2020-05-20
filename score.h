#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include "savesfile.h"
#include "QLabel"

namespace Ui {
class Score;
}

class Score : public QWidget
{
    Q_OBJECT

signals:
    void secondWindow();

public:
    Score(QWidget *parent = nullptr);
    void writeScoreOnLabel();
    void writeRewardLabel();
    ~Score();

private slots:
    void on_pushButton_clicked();



private:
    Ui::Score *ui;

    savesFile *scoreFile;
    QLabel *labelScore;
    QLabel *labelReward;
};

#endif // SCORE_H
