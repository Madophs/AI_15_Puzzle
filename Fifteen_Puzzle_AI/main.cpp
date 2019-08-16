#include "maingamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGameWindow w;
    w.setWindowTitle("Inteligencia Artificial");
    w.addButtonsToGrid();
    w.show();

    return a.exec();
}
