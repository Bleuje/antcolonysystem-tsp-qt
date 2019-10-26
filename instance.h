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
    int n; /// Number of points
    vector<int> x; /// Points x-coordinate
    vector<int> y; /// Points y-coordinate
    vector<vector<double> > dist; /// Distance matrix
    vector<list<int> > adj; /// DAG, unused so far
    QString ask_file();
    vector<vector<bool> > sub_graph; /// sub_graph is a matrix used to indicate the edges corresponding to the nearest neighbors
    double normalization;
    int DX,DY;
public:
    virtual ~Instance();
    void random_points(const int &n2, const int &dx, const int &dy);
    void write_points(QString s);
    void load_file(const int& dx,const int& dy);
};

double norm(const int &x, const int &y);

#endif // INSTANCE_H_INCLUDED
