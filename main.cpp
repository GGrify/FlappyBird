#include "widget.h"
#include "mainmenu.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    // Каждое Qt5-приложение (за исключением консольных) должно включать следующую строчку
    QApplication a(argc, argv);
    //Widget w;
    mainMenu w;
    w.setWindowTitle("Flappy bird - Demo edition");
    w.setWindowIcon(QIcon("ico.png")); // встановити иконку
    w.show();
    return a.exec();
}
