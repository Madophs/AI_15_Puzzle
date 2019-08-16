#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QMessageBox>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
typedef unsigned int unint;

namespace Ui {
class MainGameWindow;
}

class MainGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainGameWindow(QWidget *parent = nullptr);
    ~MainGameWindow();
    void addButtonsToGrid(){
        vector<int> randomNumbers = generateRandomValues();
        unint buttonId = 0;
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout = new QGridLayout(centralWidget);
        for(unint i = 0; i < rows; i++){
            buttons.push_back(vector<QPushButton*>());
            for(unint j = 0; j < cols; j++){
                QPushButton *tmpButton = new QPushButton(this);
                tmpButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                tmpButton->setText(static_cast<QString>(to_string(randomNumbers[buttonId++]).c_str()));
                if(randomNumbers[buttonId-1] == rows*cols){
                    initialHiddenButtonIndexes = {i,j};
                    QPalette palette = tmpButton->palette();
                    palette.setColor(QPalette::Button,QColor(Qt::transparent));
                    tmpButton->setAutoFillBackground(true);
                    tmpButton->setPalette(palette);
                    //tmpButton->setVisible(false);
                    tmpButton->update();
                }
                hashTable[tmpButton->text().toStdString()] = make_pair(i,j);
                buttons[i].push_back(tmpButton);
                QObject::connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(movementButtonAnimation()));
                layout->addWidget(tmpButton, static_cast<int>(i), static_cast<int>(j));
            }
        }
        setCentralWidget(centralWidget);

    }
    void hideEmptyButton(){
        buttons[initialHiddenButtonIndexes.first][initialHiddenButtonIndexes.second]->setVisible(false);
    }

public slots:
    void movementButtonAnimation(){
        string buttonId = static_cast<QPushButton*>(sender())->text().toStdString();
        unint i = hashTable.find(buttonId)->second.first;
        unint j = hashTable.find(buttonId)->second.second;
        pair<int,int> direction = whereToMove(i,j);
        if(direction != make_pair(0,0)){
            if(visibleButtonAnimation != nullptr &&  visibleButtonAnimation->currentTime() < animationDuration){
                return;
            }
            visibleButtonAnimation = new QPropertyAnimation(buttons[i][j],"geometry");
            visibleButtonAnimation->setStartValue(buttons[i][j]->geometry());
            visibleButtonAnimation->setDuration(animationDuration);
            visibleButtonAnimation->setEndValue(buttons[i+direction.first][j+direction.second]->geometry());
            nonVisibleButtonAnimation = new QPropertyAnimation(buttons[i+direction.first][j+direction.second], "geometry");
            nonVisibleButtonAnimation->setDuration(animationDuration);
            nonVisibleButtonAnimation->setStartValue(buttons[i+direction.first][j+direction.second]->geometry());
            nonVisibleButtonAnimation->setEndValue(buttons[i][j]->geometry());
            hashTable.find(buttonId)->second = {i+direction.first, j+direction.second};
            hashTable.find(buttons[i+direction.first][j+direction.second]->text().toStdString())->second = {i,j};
            swap(buttons[i][j], buttons[i+direction.first][j+direction.second]);
            nonVisibleButtonAnimation->start();
            visibleButtonAnimation->start();
        }
    }

    vector<vector<QPushButton*>> &getButtons(){
        return buttons;
    }

    void randomClicks(){
        srand(time(0));
        for(int times = 10000; times--;){
            this_thread::sleep_for(chrono::microseconds(300));
            int i = (int)rand()%rows;
            int j = (int)rand()%cols;
            //w.triggerClickedButtonEvent(i,j);
            buttons[i][j]->clicked(true);
            cout<<i<<" "<<j<<endl;
        }
    }
private:
    Ui::MainGameWindow *ui;
    QGridLayout *layout;
    QPropertyAnimation *visibleButtonAnimation{nullptr}, *nonVisibleButtonAnimation{nullptr};
    vector<vector<QPushButton*>> buttons;
    pair<int,int> initialHiddenButtonIndexes{0,0};
    unordered_map<string, pair<unint, unint>> hashTable;
    unint rows{4}, cols{4};
    int animationDuration{100};
    pair<int, int> whereToMove(int i, int j){
        string lastButtonId = to_string(rows * cols);
        if(i-1 > -1 && buttons[i-1][j]->text().toStdString() == lastButtonId){
            return {-1,0};
        }else if(j+1 < cols && buttons[i][j+1]->text().toStdString() == lastButtonId){
            return {0,1};
        }else if(i+1 < rows && buttons[i+1][j]->text().toStdString() == lastButtonId){
            return {1,0};
        }else if(j-1 > -1 && buttons[i][j-1]->text().toStdString() == lastButtonId){
            return {0,-1};
        }
        return {0,0};
    }
    vector<int> generateRandomValues(){
        srand(time(0));
        vector<int> randomNumbers(rows * cols);
        iota(randomNumbers.begin(), randomNumbers.end(), 1);
        random_shuffle(randomNumbers.begin(), randomNumbers.end());
        return randomNumbers;
    }
};

#endif // MAINGAMEWINDOW_H
