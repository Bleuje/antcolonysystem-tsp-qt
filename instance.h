#ifndef INSTANCE_H_INCLUDED
#define INSTANCE_H_INCLUDED

#include <bits/stdc++.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>
#include <QPointF>
#include <QVector>
#include <QDebug>
#include <QProgressBar>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QStyle>
#include <QDesktopWidget>
#include <QCheckBox>
#include <QFileDialog>
#include <QDate>
#include <QTime>
#include <QLabel>
#include <QPalette>
#include <QStyle>
using namespace std;

const int DX_d = 300; /// position max en x
const int DY_d = 400; /// position max en y
const int K_d = 4;
const int N_d = 30;
const int NBV_d = 500;

const int END_OF_WALK = 10;
const float EPSILON_WEIGHT = 0.000001;
const float EPSILON_GENERAL = 0.0000001;

class Instance
{
protected:
    int n; /// nombre de points
    vector<int> x; /// abscisses des points
    vector<int> y; /// ordonnées des points
    vector<vector<double> > dist; /// distances entre les points
    vector<list<int> > adj; /// A voir plus tard : graphe pour optimiser
    QString ask_file();
    vector<vector<bool> > sub_graph;
public:
    void random_points(int n2,int dx,int dy);
    void write_points(QString s);
    void load_file();
};

double norm(int x,int y);

void random_points(Instance& inst,int n,int dx,int dy);

#endif // INSTANCE_H_INCLUDED
