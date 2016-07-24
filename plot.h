#ifndef PLOT_H
#define PLOT_H

#include "colonie.h"
using namespace std;

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPointF>
#include <QVector>
#include <QDebug>
#include <QProgressBar>

void plot_best_result(QGraphicsScene * scene,Colonie & c);

void plot_pheromones(QGraphicsScene * scene,Colonie & c,int width);

void plot_colonie(QGraphicsScene * scene,Colonie & c,int width);

#endif // PLOT_H
