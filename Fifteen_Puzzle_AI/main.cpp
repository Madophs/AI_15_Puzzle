#include "maingamewindow.h"
#include <QApplication>

void randomClicks(vector<vector<QPushButton*>> buttons){
    srand(time(0));
    for(int times = 1000; times--;){
        this_thread::sleep_for(chrono::milliseconds(80));
        int i = (int)rand()%(int)buttons.size();
        int j = (int)rand()%(int)buttons.back().size();
        //w.triggerClickedButtonEvent(i,j);
        buttons[i][j]->clicked(true);
        cout<<i<<" "<<j<<endl;
    }
    cout<<"Last one"<<endl;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGameWindow w;
    w.setWindowTitle("Inteligencia Artificial");
    w.addButtonsToGrid();
    w.show();
    w.hideEmptyButton();
    std::thread hilo(randomClicks, w.getButtons());
    //hilo.join();
    return a.exec();
}
