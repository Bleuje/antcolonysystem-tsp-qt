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
    void initialise(int k,QWidget * fenetre,int dx2,int dy2);
    void load(QGraphicsScene * scene, int it,int step,double lg);
};

#endif // CVIEW_H
