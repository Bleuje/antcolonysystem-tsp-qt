#include "colonie.h"
using namespace std;

void Colonie::initialise_colonie(){
    vector<vector<double> > empty_matrix = vector<vector<double> >(n,vector<double>(n,0));
    etat.pheromone = vector<vector<double> >(n,vector<double>(n,10));;
    etat.addpheromone = empty_matrix;
    scene = new QGraphicsScene();
};

void Colonie::depose(vector<int>& traj,double longueur,double q)
{
    longueur*=longueur/10;
    for(int i=0;i+1<int(traj.size());i++){
        etat.addpheromone[traj[i]][traj[i+1]]+=q/longueur;
        etat.addpheromone[traj[i+1]][traj[i]]+=q/longueur;
    }
}

double Colonie::calcul(const vector<int>& traj)
{
    double longueur = 0.;
    for(int i=0;i+1<int(traj.size());i++){
        longueur+=dist[traj[i]][traj[i+1]];
    }
    return longueur;
}

void Colonie::update(vector<int>& traj,vector<int>& traj2,double& longueur,double& longueur2)
{
    if(longueur2<longueur)
    {
        longueur = longueur2;
        traj = traj2;
    }
    traj2 = traj;
    if(longueur<etat.longueur_min){
        etat.longueur_min = longueur;
        etat.best = traj;
    }
    if(longueur<etat.longueur_min_e){
        etat.longueur_min_e = longueur;
        etat.best_e = traj;
    }
}

void Colonie::shift(int kk,vector<int>& traj,vector<int>& traj2,double& longueur,double& longueur2)
{
    for(int i=0;i<n-kk;i++)
    {
        int aux = traj2[i];
        for(int ii=i;ii<i+kk;ii++)
        {
            traj2[ii]=traj2[ii+1];
        }
        traj2[i+kk]=aux;
        traj2[int(traj2.size())-1]=traj2[0];
        longueur2=calcul(traj2);
        update(traj,traj2,longueur,longueur2);
    }
}

void Colonie::reverse(int kk,vector<int>& traj,vector<int>& traj2,double& longueur,double& longueur2)
{
    for(int i=0;i<n-kk;i++)
    {
        vector<int> traj3 = traj2;
        for(int ii=i;ii<i+kk;ii++)
        {
            traj2[ii]=traj3[i+kk-1-(ii-i)];
        }
        traj2[int(traj2.size())-1]=traj2[0];
        longueur2=calcul(traj2);
        update(traj,traj2,longueur,longueur2);
    }
}

vector<int> Colonie::random_walk(int f)
{
    vector<int> traj;
    random_device rd; /// à mettre dans la colonie
    mt19937 gen(rd());

    /// Trajet de la fourmi
    vector<bool> used(n,0);
    used[f] = true;
    int pos = f;
    traj.push_back(pos);
    vector<double> distrib(n,0.0);
    for(int i=1;i<n;i++){
        for(int j=0;j<n;j++){
            distrib[j] = (!used[j]&&(i>=n-3||g[pos][j]) ? 0.00001 + pow(etat.pheromone[pos][j],param.alpha)*1/pow(dist[pos][j],param.beta) : 0.);
        }
        discrete_distribution<int> d(distrib.begin(),distrib.end());
        pos = d(gen);
        if(used[pos])return traj;
        used[pos]=true;
        traj.push_back(pos);
    }
    traj.push_back(f);
    return traj;
}

void Colonie::essai(int f){
    vector<int> traj = random_walk(f);
    if(int(traj.size())<=n)return;

    double longueur = calcul(traj);
    vector<int> traj2 = traj;
    double longueur2 = longueur;

    update(traj,traj2,longueur,longueur2);

    ///Recherche locale
    for(int tt=0;tt<param.nmut;tt++){
        shift(1,traj,traj2,longueur,longueur2);
        shift(2,traj,traj2,longueur,longueur2);
        if(tt%2==0) reverse(3,traj,traj2,longueur,longueur2);
        if(tt%2==0) shift(3,traj,traj2,longueur,longueur2);
        shift(3 + rand()%(n-3),traj,traj2,longueur,longueur2);
        reverse(3 + rand()%(n-3),traj,traj2,longueur,longueur2);
    }
    etat.avgsum += longueur;
    depose(traj,longueur,param.q);
}

void Colonie::actualise_pheromones(){
    etat.max_p = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            etat.pheromone[i][j] = param.rho*etat.pheromone[i][j] + etat.addpheromone[i][j];
            etat.max_p = max(etat.max_p, etat.pheromone[i][j]);
            etat.addpheromone[i][j] = 0.;
        }
    }
};

void Colonie::colonie_steps(int k)
{
    if(pause)return;

    for(int it=0;(etat.step<param.max_it)&&(it<k);it++){
        etat.avgsum = 0;
        etat.longueur_min_e = 1e12;
        int start = rand()%n;
        for(int f=0;f<param.m;f++){
            int ff = (f+start)%n;
            essai(ff);
        }
        etat.avgsum/=param.m;
        depose(etat.best_e,etat.longueur_min_e,param.e*param.q);
        actualise_pheromones();
        etat.step++;
    }
}

void Colonie::plot_points()
{
    QPen pen2(Qt::blue);
    int radius = 3;
    for(int i = 0; i < int(x.size()); i++)
        scene->addEllipse(x[i]-radius, y[i]-radius, 2*radius, 2*radius,pen2,QBrush(Qt::blue,Qt::SolidPattern));
}

void Colonie::plot_best_result()
{
    QVector <QPointF> points;
    vector<int> traj = etat.best;

    for(int i = 0; i< int(traj.size()); i++)
       points.append(QPointF(x[traj[i]], y[traj[i]]));

    QPen pen(Qt::red);
    pen.setWidth(1);
    for(int i = 0; i+1< points.size(); i++)
        scene->addLine(points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y(),pen);
}

void Colonie::plot_pheromones(int width)
{
    if(etat.step==0)width=0;
    QPen pen(Qt::green);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            int ww = min(double(width),max(0.,width*pow(etat.pheromone[i][j]/(0.0000001+etat.max_p),2)));
            pen.setWidth(ww);
            if(ww>0)
                scene->addLine(x[i], y[i], x[j], y[j], pen);
        }
    }
}

void Colonie::plot(int width)
{
    scene->clear();
    if(gpheromones)plot_pheromones(width);
    if(gbest)plot_best_result();
    plot_points();
}

void Colonie::setCView(CView & cview)
{
    cview.load(scene,param.max_it,etat.step,etat.longueur_min);
}



void Colonie::ask_parameters()
{
    Parametres_colonie c = param;
    QWidget * fenetre0 = new QWidget();
    fenetre0->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
    fenetre0->setWindowTitle("Algorithm Parameters");
    fenetre0->setFixedWidth(300);
    fenetre0->setStyleSheet("QPushButton { font-size: 10pt; background-color: lightgrey }");
    QSpinBox * mbox = new QSpinBox;
    mbox->setRange(1,1000);
    if(c.m<0)c.m=n;
    mbox->setValue(c.m);
    QDoubleSpinBox * alphabox = new QDoubleSpinBox;
    alphabox->setRange(0.,10.);
    alphabox->setValue(c.alpha);
    QDoubleSpinBox * betabox = new QDoubleSpinBox;
    betabox->setRange(0.,10.);
    betabox->setValue(c.beta);
    QDoubleSpinBox * qbox = new QDoubleSpinBox;
    qbox->setRange(10.,10000000.);
    qbox->setValue(c.q);
    QDoubleSpinBox * rhobox = new QDoubleSpinBox;
    rhobox->setRange(0.,1.);
    rhobox->setValue(c.rho);
    QSpinBox * itbox = new QSpinBox;
    itbox->setRange(1,100000);
    itbox->setValue(c.max_it);
    QSpinBox * ebox = new QSpinBox;
    ebox->setRange(0,1000);
    ebox->setValue(c.e);
    QSpinBox * nmutbox = new QSpinBox;
    nmutbox->setRange(0,10000);
    nmutbox->setValue(c.nmut);
    QSpinBox * nbvbox = new QSpinBox;
    if(c.nbv<0)c.nbv=NBV_d;
    nbvbox->setRange(5,1000);
    nbvbox->setValue(c.nbv);
    QCheckBox * gpbox = new QCheckBox;
    QCheckBox * gbbox = new QCheckBox;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Number of ants : ", mbox);
    formLayout->addRow("Alpha : ", alphabox);
    formLayout->addRow("Beta : ", betabox);
    formLayout->addRow("Q : ", qbox);
    formLayout->addRow("Conservation rho : ", rhobox);
    formLayout->addRow("Number of iterations : ", itbox);
    formLayout->addRow("Elite : ", ebox);
    formLayout->addRow("Local search iterations : ", nmutbox);
    formLayout->addRow("Number max of neighboors : ", nbvbox);
    formLayout->addRow("Show pheromones ", gpbox);
    gpbox->setChecked(gpheromones);
    formLayout->addRow("Show best result so far ", gbbox);
    gbbox->setChecked(gbest);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(formLayout);

    QPushButton *boutonOk = new QPushButton("OK");
    layoutPrincipal->addWidget(boutonOk);

    fenetre0->setLayout(layoutPrincipal);
    fenetre0->show();

    QEventLoop loop;
    QObject::connect(boutonOk, SIGNAL(clicked()), &loop, SLOT(quit()));
    loop.exec();

    param.m = mbox->value();
    param.alpha = alphabox->value();
    param.beta = betabox->value();
    param.q = qbox->value();
    param.rho = rhobox->value();
    param.max_it = itbox->value();
    param.e = ebox->value();
    param.nmut = nmutbox->value();
    gpheromones = gpbox->checkState();
    gbest = gbbox->checkState();
    setNBV(nbvbox->value());

    delete mbox;
    delete alphabox;
    delete betabox;
    delete qbox;
    delete rhobox;
    delete itbox;
    delete ebox;
    delete nmutbox;
    delete gpbox;
    delete gbbox;
    delete nbvbox;
    delete formLayout;
    delete boutonOk;
    delete layoutPrincipal;
    delete fenetre0;
}

bool Colonie::isfinished()
{
    return !(etat.step < param.max_it);
}

Colonie::~Colonie()
{
    delete scene;
}

void Colonie::write_result(QString s)
{
    if(!QDir("results").exists())
        QDir().mkdir("results");
    vector<int> traj = etat.best;
    ofstream out(("results/"+s+".txt").toStdString());
    out << etat.longueur_min << "\n";
    for(int i = 0; i < int(traj.size()); i++)
       out << traj[i] + 1 << " ";
}

void Colonie::setOptions(bool b1,bool b2)
{
    gpheromones = b1;
    gbest = b2;
}

void Colonie::setPause()
{
    pause = !pause;
}

void Colonie::stop()
{
    param.max_it = etat.step;
}

void Colonie::setNBV(int k)
{
    param.nbv = k;
    g = vector<vector<bool> >(n,vector<bool>(n,0));
    for(int i=0;i<n;i++){
        vector<pair<double,int> > tri;
        for(int j=0;j<n;j++){
            tri.push_back(make_pair(dist[i][j],j));
        }
        sort(tri.begin(),tri.end());
        for(int k=0;k<min(n,param.nbv);k++)        {
            g[i][tri[k].second] = true;
        }
    }
}

bool isfinished(Colonie * colonies,int k){
    for(int i=0;i<k;i++){
        if(!((colonies + i)->isfinished()))
            return false;
    }
    return true;
}
