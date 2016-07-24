#ifndef COLONIE_H_INCLUDED
#define COLONIE_H_INCLUDED

#include "instance.h"
#include "cview.h"
using namespace std;

const double Beta = 2.;
const double Alpha = 6.;
const int Q = 10000;
const int MAX_IT = 250;
const double Rho = 0.95;
const double E = 20.;
const int NMut = 100;

class CView;

struct Parametres_colonie
{
    int m = -1; /// nombre de fourmis
    double alpha = Alpha; /// importance des phéromones
    double beta = Beta; /// Importance de la distance
    double q = Q; /// Facteur de quantité de phéromones déposées
    double rho = Rho; /// coefficient d'évaporation
    double max_it = MAX_IT; /// Nombre d'itérations
    double e = E; /// paramètre pour les fourmis élitistes
    int nmut = NMut;
    int nbv = -1; /// nombre de voisins
};

struct Etat_colonie
{
    vector<vector<double> > pheromone; /// phéromones sur l'arc i -> j
    vector<vector<double> > addpheromone; /// phéromones à ajouter sur l'arc i -> j
    vector<int> best;
    vector<int> best_e;
    double longueur_min = 1e15;
    double longueur_min_e = 1e15;
    double avgsum = 0.;
    double max_p = 0.;
    int step = 0;
};

class Colonie : public Instance
{
private:
    Etat_colonie etat;
    Parametres_colonie param;
    vector<int> random_walk(int f);
    void depose(vector<int>& traj,double longueur,double q);
    double calcul(const vector<int>& traj);
    void update(vector<int>& traj,vector<int>& traj2,double& longueur,double& longueur2);
    void shift(int kk,vector<int>& traj,vector<int>& traj2,double& longueur,double& longueur2);
    void reverse(int kk,vector<int>& traj,vector<int>& traj2,double& longueur,double& longueur2);
    void essai(int f);
    void actualise_pheromones();
    void plot_points();
    void plot_best_result();
    void plot_pheromones(int width);
    QGraphicsScene * scene;
    bool gpheromones = true;
    bool gbest = true;
    bool pause = false;
public:
    ~Colonie();
    void initialise_colonie();
    void colonie_steps(int k);
    void plot(int width);
    void setCView(CView & cview);
    void setNBV(int k);
    void ask_parameters();
    bool isfinished();
    void write_result(QString s);
    void setOptions(bool b1,bool b2);
    void setPause();
    void stop();
};

bool isfinished(Colonie * colonies,int k);

#endif // COLONIE_H_INCLUDED
