#include "savesfile.h"
#include "QDebug"
#include <QDir>

savesFile::savesFile()
{

}

int savesFile::readFileLvl()
{

    file.setFileName(QDir::currentPath() + "/saves.txt");
    // С помощью метода open() открываем файл в режиме чтения
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << QDir::currentPath();
      qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
      return -1; //тут треба придумати якусь помилку
    }
    QTextStream in(&file);

      QString line = in.readLine(); // метод readLine() считывает одну строку из потока
      if (QString::compare(line, "Lvl: 1") == 0)
          return 1;

      if (QString::compare(line, "Lvl: 2") == 0)
          return 2;

      file.close();
      return 0;
}

void savesFile::writeFileLvl(QString lvl)
{
    QTextStream out(stdout);
    file.setFileName(QDir::currentPath() + "/saves.txt");

    // Открываем файл в режиме "Только для записи"
    if (file.open(QIODevice::WriteOnly)) {
        qDebug() << "WRITING ON FILE";
        QTextStream out(&file); // поток записываемых данных направляем в файл
        out << lvl << endl;
    } else {
        qWarning("Could not open file");
    }
    file.close();
}

int savesFile::getFileScore()
{
    file.setFileName(QDir::currentPath() + "/score");
    if (!file.open(QIODevice::ReadOnly)) {
      qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
      return -1; //тут треба придумати якусь помилку
    }
    QTextStream in(&file);

    // Считываем файл строка за строкой
    QString line = in.readLine(); // саме остання строка містить наш Score
    file.close();
    return line.toInt();
}

void savesFile::writeFileScore(int score)
{
    QTextStream out(stdout);
    file.setFileName(QDir::currentPath() + "/score");

    // Открываем файл в режиме "Только для записи"
    if (file.open(QIODevice::WriteOnly)) {
        qDebug() << "WRITING ON FILE";
        QTextStream out(&file); // поток записываемых данных направляем в файл
        out << score << endl;
    } else {
        qWarning("Could not open file");
    }
    file.close();
}

