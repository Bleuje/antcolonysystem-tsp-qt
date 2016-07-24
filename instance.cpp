#include "instance.h"
using namespace std;

double norm(int x,int y){
    return sqrt(x*x + y*y);
}

void Instance::random_points(int n2,int dx,int dy)
{
    srand (time(NULL));

    n = n2;
    x = vector<int>(n);
    y = vector<int>(n);
    vector<vector<double> > empty_matrix = vector<vector<double> >(n,vector<double>(n));
    dist = empty_matrix;
    for(int i=0;i<n;i++){
        x[i] = dx/10 + rand()%(dx-2*dx/10);
        y[i] = dy/10 + rand()%(dy-2*dy/10);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            double calcul = norm(x[i]-x[j],y[i]-y[j]);
            dist[i][j] = calcul;
            dist[j][i] = calcul;
        }
    }
}

void Instance::write_points(QString s)
{
    if(!QDir("problems").exists())
        QDir().mkdir("problems");
    ofstream out(("problems/"+s+".txt").toStdString());
    out << n << "\n";
    for(int i = 0; i < n; i++)
       out << x[i] << " " << y[i] << "\n";
}

QString Instance::ask_file()
{
    QWidget *  fen = new QWidget();
    QString fichier = QFileDialog::getOpenFileName(fen, "Ouvrir un fichier", QString());
    delete fen;
    return fichier;
}


void Instance::load_file()
{
    QString str = ask_file();
    if(str==NULL)return;
    ifstream in(str.toStdString());
    in >> n;
    x = vector<int>(n);
    y = vector<int>(n);
    vector<vector<double> > empty_matrix = vector<vector<double> >(n,vector<double>(n));
    dist = empty_matrix;
    for(int i=0;i<n;i++){
        in >> x[i];
        in >> y[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            double calcul = norm(x[i]-x[j],y[i]-y[j]);
            dist[i][j] = calcul;
            dist[j][i] = calcul;
        }
    }
}
