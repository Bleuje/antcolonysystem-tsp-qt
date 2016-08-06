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
const double BIG_DOUBLE = 1e15;




class Colony_view;

struct Colony_parameters
{
    int m = -1; /// nunmber of ants per iteration
    double alpha = Alpha; /// ACS parameter : importance of pheromones
    double beta = Beta; /// ACS parameter : importance of distance
    double q = Q; /// Quantity of pheromones factor
    double rho = Rho; /// Coefficient of pheromones disappearance
    double max_it = MAX_IT; /// Maximum number of iterations
    double e = E; /// Importance og the elitist path
    int number_of_mutations = NMut; /// Number of mutations (local search optimization)
    int number_of_neighbors = -1; /// Number of neighbors for each node (in the sub_graph)
};

struct Colony_state
{
    vector<vector<double> > pheromone; /// pheromones quantity on i -> j
    vector<vector<double> > add_pheromone; /// pheromones quantity to add at the end of the iteration, on i -> j
    vector<int> best_path;
    vector<int> best_path_elite;
    double min_length = BIG_DOUBLE;
    double min_length_elite = BIG_DOUBLE;
    double average_length = 0.;
    double max_p = 0.;
    int step = 0;
};





// Colony is defined as a class, and as a particular case of an Instance (just for code factorization
// It contains methods and attributes that make its colony state (Colony_state) evolve.
// It contains a function that opens a window to change its parameters (ask_parameters()).
// It containts a Qt graphical scene, and functions to update it.
// Actually ploting the scene on the screen is done under the class Colony_view, after transferring the scene to an instance of Colony_view.

class Colony : public Instance
{

private:
    Colony_state etat;
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
