#include "plot.h"
using namespace std;
/*
void Colonie::plot_best_result()
{
    QVector <QPointF> points;
    vector<int> traj = etat.best;

    for(int i = 0; i< int(traj.size()); i++)
       points.append(QPointF(c.x[traj[i]], c.y[traj[i]]));

    QPen pen(Qt::red);
    pen.setWidth(1);
    for(int i = 0; i+1< points.size(); i++)
        scene->addLine(points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y(),pen);

    QPen pen2(Qt::blue);
    int radius = 4;
    for(int i = 0; i< points.size(); i++)
        scene->addEllipse(points[i].x()-radius, points[i].y()-radius, 2*radius, 2*radius,pen2,QBrush(Qt::blue,Qt::SolidPattern));
}

void Colonie::plot_pheromones(int width)
{
    QPen pen(Qt::green);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            int ww = width*pow(etat.pheromone[i][j]/(0.0000001+etat.max_p),2);
            pen.setWidth(ww);
            if(ww>0)
                scene->addLine(x[i], y[i], x[j], y[j], pen);
        }
    }
}

void plot_colonie(QGraphicsScene * scene,Colonie & c,int width)
{
    scene->clear();
    plot_pheromones(scene,c,width);
    plot_best_result(scene,c);
}

*/


