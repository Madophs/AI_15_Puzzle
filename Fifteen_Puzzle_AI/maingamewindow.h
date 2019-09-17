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
#include <chrono>
#include "aithread.h"

using namespace std;
typedef unsigned int unint;

namespace Ui {
class MainGameWindow;
}

class AIThread;

class MainGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainGameWindow(QWidget *parent = nullptr);
    ~MainGameWindow();
    bool solvable(vector<int>);
    void addButtonsToGridLayout();
    void hideEmptyButton();
public slots:
    void movementButtonAnimation();
    void shuffleButtons();
    vector<vector<QPushButton*>> &getButtons();
    void startAI();
    void exitProgram();
    void changePuzzleId();
private:
    Ui::MainGameWindow *ui;
    AIThread *aiThread{nullptr};
    QGridLayout *layout;
    QPropertyAnimation *visibleButtonAnimation{nullptr}, *nonVisibleButtonAnimation{nullptr};
    vector<vector<QPushButton*>> buttons;
    vector<QAction*> puzzlesCheckbox;
    pair<int,int> initialHiddenButtonIndexes{0,0};
    unordered_map<string, pair<unint, unint>> hashTable;
    unint rows{4}, cols{4};
    int animationDuration{70};
    pair<int, int> whereToMove(int i, int j);
    vector<int> generateRandomValues();
    QPalette getCorrespondentPalette(int, QPushButton *&);
    void initializeAIThread();
    void togglePuzzleCheckbox(QString);
};

#endif // MAINGAMEWINDOW_H
