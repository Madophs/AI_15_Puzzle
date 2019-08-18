#include "maingamewindow.h"
#include "ui_maingamewindow.h"
#include <QLabel>
#include <QPixmap>

MainGameWindow::MainGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainGameWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionReiniciar, SIGNAL(triggered()), this, SLOT(startAI()));
    QObject::connect(ui->actionMezclar, SIGNAL(triggered()), this, SLOT(shuffleButtons()));
    QObject::connect(ui->actionSalir, SIGNAL(triggered()),this,SLOT(exitProgram()));
}

MainGameWindow::~MainGameWindow()
{
    delete ui;
}

/* Public functions ans methods */

bool MainGameWindow::solvable(vector<int> puzzle){
    int inversions = 0, emptyCellLocation = 0;
    for(int i = 0; i < rows * cols; i++){
        for(int j = i+1; j < puzzle.size(); j++){
            if(puzzle[i] != 16 && puzzle[j] != 16 && puzzle[i] > puzzle[j])
                ++inversions;
            if(puzzle[i] == 16 || puzzle[j] == 16){
                if(puzzle[i] == 16)
                    emptyCellLocation = i / 4;
                else
                    emptyCellLocation = j / 4;
            }
        }
    }
    if(emptyCellLocation%2 == 0 && inversions&1) return true;
    if(emptyCellLocation&1 && inversions%2 == 0) return true;
    return false;
}

void MainGameWindow::addButtonsToGridLayout(){
    vector<int> randomNumbers;
    do{
        randomNumbers = generateRandomValues();
    }while(!solvable(randomNumbers));
    unint buttonId = 0;
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout = new QGridLayout(centralWidget);
    QFont mdsFont;
    mdsFont.setPointSize(30);
    mdsFont.setBold(true);
    for(unint i = 0; i < rows; i++){
        buttons.push_back(vector<QPushButton*>());
        for(unint j = 0; j < cols; j++){
            QPushButton *tmpButton = new QPushButton(this);
            tmpButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            tmpButton->setText(static_cast<QString>(to_string(randomNumbers[buttonId++]).c_str()));
            tmpButton->setFont(mdsFont);
            if(randomNumbers[buttonId-1] == rows*cols){
                initialHiddenButtonIndexes = {i,j};
            }
            hashTable[tmpButton->text().toStdString()] = make_pair(i,j);
            buttons[i].push_back(tmpButton);
            QObject::connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(movementButtonAnimation()));
            layout->addWidget(tmpButton, static_cast<int>(i), static_cast<int>(j));
        }
    }
    setCentralWidget(centralWidget);
}

void MainGameWindow::hideEmptyButton(){
    buttons[initialHiddenButtonIndexes.first][initialHiddenButtonIndexes.second]->setVisible(false);
}

/* Public Slots */

void MainGameWindow::movementButtonAnimation(){
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
void MainGameWindow::shuffleButtons(){
    if(aiThread != nullptr){
        if(aiThread->isFinished()){;
            aiThread->setShuffle(true);
            aiThread->start();
        }else{
            aiThread->setShuffle(true);
            aiThread->terminate();
            while(!aiThread->isFinished()) aiThread->usleep(30);
            aiThread->start();
        }
    }else{
        aiThread = new AIThread(this);
        connect(aiThread, &AIThread::emitClick,[&](int i, int j){
           buttons[i][j]->click();
           cout<<i<<" "<<j<<endl;
        });
        connect(aiThread, &AIThread::showMessage,[&](QString message, QString title){
            QMessageBox msg;
            msg.setWindowTitle(title);
            msg.setText(message);
            msg.exec();
        });
        aiThread->setShuffle(true);
        aiThread->start();
    }
}
vector<vector<QPushButton*>> &MainGameWindow::getButtons(){
    return buttons;
}

void MainGameWindow::exitProgram(){
    this->close();
}

void MainGameWindow::startAI(){
    if(aiThread != nullptr){
        aiThread->setShuffle(false);
        if(aiThread->isFinished()){;
            aiThread->setPuzzleGridLayout(buttons);
            aiThread->start();
        }else{
            aiThread->terminate();
            while(!aiThread->isFinished()) aiThread->usleep(30);
            aiThread->setPuzzleGridLayout(buttons);
            aiThread->start();
        }
    }else{
        aiThread = new AIThread(this);
        aiThread->setPuzzleGridLayout(buttons);
        connect(aiThread, &AIThread::emitClick,[&](int i, int j){
           buttons[i][j]->click();
           cout<<i<<" "<<j<<endl;
        });
        connect(aiThread, &AIThread::showMessage,[&](QString message, QString title){
            QMessageBox msg;
            msg.setWindowTitle(title);
            msg.setText(message);
            msg.exec();
        });
        aiThread->setShuffle(false);
        aiThread->start();
    }
}

/* private function and methods */

pair<int, int> MainGameWindow::whereToMove(int i, int j){
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
vector<int> MainGameWindow::generateRandomValues(){
    srand(time(0));
    vector<int> randomNumbers(rows * cols);
    iota(randomNumbers.begin(), randomNumbers.end(), 1);
    random_shuffle(randomNumbers.begin(), randomNumbers.end());
    return randomNumbers;
}

