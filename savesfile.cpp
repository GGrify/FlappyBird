#include "savesfile.h"
#include "QDebug" //для дебагінгу використовували
#include <QDir>

savesFile::savesFile(){}

int savesFile::readFileLvl()
{
    QFileInfo checkFile(QDir::currentPath() + "/saves.txt"); //перевірити чи існує saves.txt

    //якщо файл не існує, ми його створимо самі
    if (!checkFile.exists() && !checkFile.isFile()) {
        file.setFileName(QDir::currentPath() + "/saves.txt");
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file); // поток записываемых данных направляем в файл
        out << "Lvl: 1" << endl; //починаємо гру з першого рівня
        this->writeFileScore(0); //рахунок очок також онуляємо
        file.close();
        return 1;
    }

    file.setFileName(QDir::currentPath() + "/saves.txt");
    if (!file.open(QIODevice::ReadOnly)) { //відкриваємо файл в режимі для зчитування
        qWarning("Cannot open file for reading"); // якщо файл не знайдено(для дебагінгу)
        return -1;
    }

    QTextStream in(&file); //Клас QTextStream надає зручний інтерфейс для зчитування і запису тексту

    QString line = in.readLine(); // метод readLine() считывает одну строку из потока

    if (QString::compare(line, "Lvl: 1") == 0) return 1;
    if (QString::compare(line, "Lvl: 2") == 0) return 2;
    if (QString::compare(line, "Lvl: end") == 0) return 0;

    file.close();
    return -1; //якщо щось пішло не так
}

void savesFile::writeFileLvl(QString lvl)
{
    QTextStream out(stdout);
    file.setFileName(QDir::currentPath() + "/saves.txt");

    if (file.open(QIODevice::WriteOnly)) { //відкриваємо файл в режимі тільки для запису
        QTextStream out(&file); // поток записываемых данных направляем в файл
        out << lvl << endl;
    } else {
        qWarning("Could not open file");
    }
    file.close();
}

int savesFile::getFileScore()
{
    QFileInfo checkFile(QDir::currentPath() + "/score"); //перевірити чи існує score

    //якщо файл не існує, ми його створимо самі
    if (!checkFile.exists() && !checkFile.isFile()) {
        file.setFileName(QDir::currentPath() + "/score");
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file); // поток записываемых данных направляем в файл
        out << "0" << endl; //починаємо гру з першого рівня
        file.close();
        return 0; //повертаємо теперішній рахунок
    }

    file.setFileName(QDir::currentPath() + "/score");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
        return -1;
    }
    QTextStream in(&file);

    // Считываем файл строка за строкой
    QString line = in.readLine();
    file.close();

    return line.toInt();
}

void savesFile::writeFileScore(int score)
{ 
    file.setFileName(QDir::currentPath() + "/score");

    if (file.open(QIODevice::WriteOnly)) { // Открываем файл в режиме "Только для записи"
        QTextStream out(&file); // поток записываемых данных направляем в файл
        out << score << endl;
    } else {
        qWarning("Could not open file");
    }
    file.close();
}

