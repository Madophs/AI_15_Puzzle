#include "maingamewindow.h"
//#include "fifteen_puzzle.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGameWindow w;
    w.setWindowTitle("Inteligencia Artificial");
    w.addButtonsToGridLayout();
    //w.setFixedSize(600,600);
    w.show();
    w.hideEmptyButton();
    //thread hilo(solvePuzzle, w.getButtons());
    return a.exec();
}
