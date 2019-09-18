#include "maingamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGameWindow w;
    w.setWindowTitle("Inteligencia Artificial");
    w.addButtonsToGridLayout();
    w.setFixedSize(650, 650);
    w.show();
    w.hideEmptyButton();
    return a.exec();
}
