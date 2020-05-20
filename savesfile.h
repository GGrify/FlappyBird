#ifndef SAVESFILE_H
#define SAVESFILE_H

#include "QFile"
#include <QTextStream>
#include <QFileInfo>

#define lvlTwoScore 3
#define lastLvlScore 4


class savesFile
{
public:
    savesFile();
    ~savesFile();
    int readFileLvl();
    void writeFileLvl(QString lvl);
    int getFileScore();
    void writeFileScore(int score);

private:
    QFile file;

};

#endif // SAVESFILE_H
