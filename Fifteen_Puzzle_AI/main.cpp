#include "maingamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGameWindow w;
    w.setWindowTitle("Inteligencia Artificial");
    w.addButtonsToGridLayout();
    w.show();
    w.hideEmptyButton();
    return a.exec();
}
