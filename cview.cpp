#include "cview.h"

Colony_view::~Colony_view()
{
    qDebug() << "Began cview destructor" << endl;
    delete view;
    delete but;
    delete but2;
    delete but3;
    delete but4;
    delete bar;
    qDebug() << "Finished cview destructor" << endl;
}

Colony_view::Colony_view(const Colony_view& cv)
{
    qDebug() << "In copy constructor\n";
    index = cv.index;
    dx=cv.dx;
    dy=cv.dy;
    win = cv.win;
    int k = index-1;
    view = new QGraphicsView(win);
    view->setFixedSize(dx, max(10,dy-50));
    view->move(k*dx,25);
    but = new QLabel(win);
    but->setFixedSize(dx/2, 25);
    but->move(k*dx,0);
    but2 = new QPushButton(win);
    but2->setFixedSize(dx/6, 25);
    but2->move(k*dx+dx/2,0);
    but3 = new QPushButton(win);
    but3->setFixedSize(dx/6, 25);
    but3->move(k*dx+4*dx/6,0);
    but4 = new QPushButton(win);
    but4->setFixedSize(dx/6, 25);
    but4->move(k*dx+5*dx/6,0);
    bar = new QProgressBar(win);
    bar->setRange(0,1);
    bar->setFixedSize(dx, 25);
    bar->move(k*dx,dy-25);
}

Colony_view::Colony_view(const int& k,QWidget * window,const int& dx2,const int& dy2)
{
    win = window;
    index = k+1;
    dx=dx2;
    dy=dy2;
    view = new QGraphicsView(window);
    view->setFixedSize(dx, max(10,dy-50));
    view->move(k*dx,25);
    but = new QLabel(window);
    but->setFixedSize(dx/2, 25);
    but->move(k*dx,0);
    but2 = new QPushButton(window);
    but2->setFixedSize(dx/6, 25);
    but2->move(k*dx+dx/2,0);
    but3 = new QPushButton(window);
    but3->setFixedSize(dx/6, 25);
    but3->move(k*dx+4*dx/6,0);
    but4 = new QPushButton(window);
    but4->setFixedSize(dx/6, 25);
    but4->move(k*dx+5*dx/6,0);
    bar = new QProgressBar(window);
    bar->setRange(0,1);
    bar->setFixedSize(dx, 25);
    bar->move(k*dx,dy-25);
}

void Colony_view::connect(SetThings * s)
{
    QObject::connect(but2, SIGNAL(clicked()), s, SLOT(setting()));
    QObject::connect(but3, SIGNAL(clicked()), s, SLOT(pause()));
    QObject::connect(but4, SIGNAL(clicked()), s, SLOT(stop()));
}

void Colony_view::load(QGraphicsScene * scene,const int& it,const int& step,const double& lg)
{
    view->setScene(scene);
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio );
    bar->setRange(0,it);
    bar->setValue(step);
    bar->setFormat(QString::number(step) + " / " + QString::number(it));
    but->setText((lg<1e10?QString::number(lg):"Nothing"));
    but->setStyleSheet("QLabel {font-size: 10pt; font-weight: bold;qproperty-alignment: AlignCenter;}");
    but2->setText("Edit");
    but3->setText("Pause");
    but4->setText("Stop");
}
