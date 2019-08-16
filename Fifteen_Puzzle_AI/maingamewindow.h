#ifndef MAINGAMEWINDOW_H
#define MAINGAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QPushButton>
#include <cmath>
#include <vector>

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
        unint buttonId = 0;
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout = new QGridLayout(centralWidget);
        for(unint i = 0; i < rows; i++){
            buttons.push_back(vector<QPushButton*>());
            for(unint j = 0; j < cols; j++){
                QPushButton *tmpButton = new QPushButton(this);
                tmpButton->setText(to_string(++buttonId).c_str());
                tmpButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                buttons[i].push_back(tmpButton);
                layout->addWidget(tmpButton, static_cast<int>(i), static_cast<int>(j));
            }
        }
        setCentralWidget(centralWidget);
    }

private:
    Ui::MainGameWindow *ui;
    QGridLayout *layout;
    vector<vector<QPushButton*>> buttons;
    unint rows{4}, cols{4};
};

#endif // MAINGAMEWINDOW_H
