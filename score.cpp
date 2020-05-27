#include "score.h"
#include "ui_score.h"

Score::Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Score)
{
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    ui->setupUi(this);
    scoreFile = new savesFile();

    labelScore = new QLabel(this);
    labelReward = new QLabel(this);


}

Score::~Score()
{
    delete ui;
}

void Score::on_pushButton_clicked()
{
    this->close();
    emit secondWindow(); // И вызываем сигнал на открытие главного окна
}

void Score::writeScoreOnLabel()
{

    labelScore->setText("99");
    labelScore->setGeometry(251,64,45,25);
    labelScore->setStyleSheet("QLabel { color : #fff; font-size: 28px; }");
    labelScore->setText(QString::number(scoreFile->getFileScore()));

}

void Score::writeRewardLabel()
{
    labelReward->setText("<a style=\"color: #fff; text-decoration: underline;\" href=\"https://freesteam.ru/\">Great! Click to claim reward...</a>");
    labelReward->setTextInteractionFlags(Qt::TextBrowserInteraction);
    labelReward->setOpenExternalLinks(true);
    labelReward->setGeometry(140,150,231,18);
    labelReward->setStyleSheet("QLabel { color : #fff; font-size: 18px; }");

}
