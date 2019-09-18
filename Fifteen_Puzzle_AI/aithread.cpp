#include "aithread.h"
#include "fifteen_puzzle.h"
#include <iostream>
#include <random>
#include <ctime>

AIThread::AIThread(QObject *parent) : QThread(parent)
{

}

void AIThread::setPuzzleGridLayout(vector<vector<QPushButton *>> buttons){
    this->puzzleGrid.clear();
    for(int i = 0; i < buttons.size(); i++){
        this->puzzleGrid.push_back(vector<int>());
        for(int j = 0; j < buttons.back().size(); j++){
            int integerValue = atoi(buttons[i][j]->text().toStdString().c_str());
            this->puzzleGrid.back().push_back(integerValue);
        }
    }
}

void AIThread::setShuffle(bool shuffle){
    this->shuffle = shuffle;
}

void AIThread::setPuzzleId(int puzzleId){
    this->puzzleId = puzzleId;
}

void AIThread::run(){
    if(shuffle){
        cout<<"Mezclando"<<endl;
        srand(time(0));
        for(int clicks = 500; clicks--;){
            int i = (int)rand() % 4;
            int j = (int)rand() % 4;
            emit emitClick(i,j);
            msleep(30);
        }
    }else{
        cout<<"Ejecutando algoritmo"<<endl;
        string movements = generateSolution(puzzleGrid, puzzleId);
        if(!movements.empty())
            cout<<"Resolviendo..."<<endl;
        cout<<movements<<endl;
        int i = 0, j = 0;
        bool emptyCellFound = false;
        for(i = 0; i < puzzleGrid.size() && !emptyCellFound; i++){
            for(j = 0; j < puzzleGrid.back().size() && !emptyCellFound; j++){
                if(puzzleGrid[i][j] == 16){
                    emptyCellFound = true;
                }
            }
        }
        --i, --j;
        for(int x = 0; x < movements.length(); x++){
            msleep(300);
            if(movements[x] == 'U'){
                emit emitClick(--i, j);
            }else if(movements[x] == 'D'){
                emit emitClick(++i,j);
            }else if(movements[x] == 'L'){
                emit emitClick(i, --j);
            }else{
                emit emitClick(i, ++j);
            }
        }
        if(movements.empty() && !alreadySolved){
            emit showMessage("No se pudo encontrar la solución", "Madophs AI");
        }else if(!movements.empty()){
            emit showMessage("15 Puzzle ha sido resuelto!!!","Madophs AI");
        }else{
            emit showMessage("15 Puzzle ya ha sido resuelto!!!","Madophs AI");
        }
        alreadySolved = false;
    }
    shuffle = false;
}
