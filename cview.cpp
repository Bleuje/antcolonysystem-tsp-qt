#include "cview.h"

Colony_view::~Colony_view()
{
    delete view;
    delete but;
    delete but2;
    delete but3;
    delete but4;
    delete bar;
}

void Colony_view::load(QGraphicsScene * scene, int it, int step, double lg)
{
    view->setScene(scene);
    bar->setRange(0,it);
    bar->setValue(step);
    bar->setFormat(QString::number(step) + " / " + QString::number(it));
    but->setText((lg<1e10?QString::number(lg):"Nothing"));
    but->setStyleSheet("QLabel {font-size: 10pt; font-weight: bold;qproperty-alignment: AlignCenter;}");
    but2->setText("Edit");
    but3->setText("Pause");
    but4->setText("Stop");
}

void Colony_view::initialise(int k,QWidget * fenetre,int dx2,int dy2)
{
    index = k+1;
    dx=dx2;
    dy=dy2;
    view = new QGraphicsView(fenetre);
    view->setFixedSize(dx, max(10,dy-50));
    view->move(k*dx,25);
    but = new QLabel(fenetre);
    but->setFixedSize(dx/2, 25);
    but->move(k*dx,0);
    but2 = new QPushButton(fenetre);
    but2->setFixedSize(dx/6, 25);
    but2->move(k*dx+dx/2,0);
    but3 = new QPushButton(fenetre);
    but3->setFixedSize(dx/6, 25);
    but3->move(k*dx+4*dx/6,0);
    but4 = new QPushButton(fenetre);
    but4->setFixedSize(dx/6, 25);
    but4->move(k*dx+5*dx/6,0);
    bar = new QProgressBar(fenetre);
    bar->setRange(0,1);
    bar->setFixedSize(dx, 25);
    bar->move(k*dx,dy-25);
}

void Colony_view::connect(SetThings * s)
{
    QObject::connect(but2, SIGNAL(clicked()), s, SLOT(reglage()));
    QObject::connect(but3, SIGNAL(clicked()), s, SLOT(pause()));
    QObject::connect(but4, SIGNAL(clicked()), s, SLOT(stop()));
}
