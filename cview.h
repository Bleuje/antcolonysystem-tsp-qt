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
public:
    ~Colony_view();
    void connect(SetThings * s);
    void initialize(const int& k,QWidget * window,const int& dx2,const int& dy2);
    void load(QGraphicsScene * scene,const int& it,const int& step,const double& lg,const double& norm);
};

#endif // CVIEW_H
