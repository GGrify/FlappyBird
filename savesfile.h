#ifndef SAVESFILE_H
#define SAVESFILE_H

#include "QFile"
#include <QTextStream>
#include <QFileInfo>


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
