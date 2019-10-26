#ifndef CVIEW_H
#define CVIEW_H

#include "instance.h"

#include "interface.h"

class Colony;

class SetThings;

class Colony_view
{
private:
    int index;
    int dx;
    int dy;
    QGraphicsView * view;
    QLabel * but;
    QProgressBar * bar;
    QPushButton * but2;
    QPushButton * but3;
    QPushButton * but4;
    QWidget * win;
public:
    ~Colony_view();
    Colony_view(const Colony_view& cv);
    Colony_view(const int& k,QWidget * window,const int& dx2,const int& dy2);
    void connect(SetThings * s);
    void load(QGraphicsScene * scene,const int& it,const int& step,const double& lg);
};

#endif // CVIEW_H
