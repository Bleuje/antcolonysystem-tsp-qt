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

class Colony_view;

struct Colony_parameters
{
    int m = -1; /// nombre de fourmis
    double alpha = Alpha; /// importance des phéromones
    double beta = Beta; /// Importance de la distance
    double q = Q; /// Facteur de quantité de phéromones déposées
    double rho = Rho; /// coefficient d'évaporation
    double max_it = MAX_IT; /// Nombre d'itérations
    double e = E; /// paramètre pour les fourmis élitistes
    int nmut = NMut;
    int number_of_neighbors = -1; /// nombre de voisins
};

struct Etat_colonie
{
    vector<vector<double> > pheromone; /// phéromones sur l'arc i -> j
    vector<vector<double> > add_pheromone; /// phéromones à ajouter sur l'arc i -> j
    vector<int> best_path;
    vector<int> best_path_elite;
    double min_length = 1e15;
    double min_length_elite = 1e15;
    double average_length = 0.;
    double max_p = 0.;
    int step = 0;
};

class Colony : public Instance
{
private:
    Etat_colonie etat;
    Colony_parameters param;
    vector<int> random_walk(const int& f);
    void add_pheromones_from_walk(vector<int>& path,double length,double q);
    double compute_length(const vector<int>& path);
    void update(vector<int>& path,vector<int>& path2,double& length,double& length2);
    void shift(const int &kk, vector<int>& path, vector<int>& path2, double& length, double& length2);
    void reverse(const int& kk,vector<int>& path,vector<int>& path2,double& length,double& length2);
    void ant_try(const int& f);
    void update_pheromones();
    void plot_points();
    void plot_best_result();
    void plot_pheromones(int width);
    QGraphicsScene * scene;
    bool display_pheromones = true;
    bool display_best_walk = true;
    bool pause = false;
public:
    Colony();
    ~Colony();
    void initialize_colony();
    void colonie_steps(const int& k);
    void plot(const int& width);
    void set_colony_view(Colony_view & cview);
    void set_neighbors_graph(const int& k);
    void ask_parameters();
    bool is_finished();
    void write_result(QString s);
    void set_options(bool b1,bool b2);
    void set_pause();
    void stop();
};

bool is_finished(Colony * colonies,const int& k);

#endif // COLONIE_H_INCLUDED
