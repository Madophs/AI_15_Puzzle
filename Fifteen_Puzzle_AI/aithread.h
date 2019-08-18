#ifndef AITHREAD_H
#define AITHREAD_H

#include <QObject>
#include <QThread>
#include <QPushButton>
#include <vector>

using namespace std;

class AIThread : public QThread
{
    Q_OBJECT
public:
    explicit AIThread(QObject *parent = nullptr);
    void setPuzzleGridLayout(vector<vector<QPushButton*>>);
    void setShuffle(bool);
signals:  
    void emitClick(int, int);
    void showMessage(QString, QString);
public slots:

protected:
   void run() override;
private:
   vector<vector<int>> puzzleGrid;
   bool shuffle{false};
};

#endif // AITHREAD_H
