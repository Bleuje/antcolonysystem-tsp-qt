#include "interface.h"
using namespace std;

// plus de commentaires, décrire les méthodes, documenter les contraintes sur les paramètres.
// bien documenter les méthodes
// faire des classes telles qu'on puisse les utiliser sans regarder le code
// conventions de nommage
// eviter de mélanger français anglais
// plus de constantes


int main(int argc, char *argv[])
{
    QApplication * a = new QApplication(argc, argv);

    /// Initialisation du problème
    int K,n,DX,DY;
    bool choice = ask_main_parameters(K,n,DX,DY);
    Colonie c;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    c.random_points(n,DX,DY);
    if(choice){c.load_file();}
    else{/// Sauvegarde du problème
        c.write_points("Instance_"+date.toString("dd-MM-yyyy")+"_"+time.toString("hh-mm-ss"));
    }

    /// Demande des paramètres généraux de l'algorithme
    c.ask_parameters();

    /// Creation des colonies
    Colonie * colonies = new Colonie[K];
    for(int i=0;i<K;i++){
        colonies[i]=c;
        colonies[i].initialise_colonie();
    }


    /// Creation de la grande fenetre
    DX = min(DX,QApplication::desktop()->screenGeometry().width()/K);
    DY = min(DY,QApplication::desktop()->screenGeometry().height()-200);
    QWidget * fenetre = new QWidget();
    fenetre->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

    QPushButton * run = new QPushButton(fenetre);
    QPushButton * close = new QPushButton(fenetre);
    QPushButton * pause = new QPushButton(fenetre);
    QPushButton * stop = new QPushButton(fenetre);
    run->setFixedSize(K*DX/4,25);
    run->move(0,DY);
    run->setText("Run");
    run->setStyleSheet("QPushButton { font-size: 10pt; font-weight: bold; color: green ;}");
    pause->setFixedSize(K*DX/4,25);
    pause->move(K*DX/4,DY);
    pause->setText("Pause");
    pause->setStyleSheet("QPushButton { font-size: 10pt; font-weight: bold; color: blue ;}");
    stop->setFixedSize(K*DX/4,25);
    stop->move(2*K*DX/4,DY);
    stop->setText("Stop");
    stop->setStyleSheet("QPushButton { font-size: 10pt; font-weight: bold; color: #bb0000 ;}");
    close->setFixedSize(K*DX/4,25);
    close->move(3*K*DX/4,DY);
    close->setText("Close");
    close->setStyleSheet("QPushButton { font-size: 10pt; font-weight: bold; color: black ;}");
    fenetre->setWindowTitle("Improved Ant Colony System Algorithm");

    SetThings * connexions = new SetThings[K];
    SetThings * global = new SetThings();
    global->fenetre = fenetre;
    CView * cviews = new CView[K];
    for(int i=0;i<K;i++)
    {
        cviews[i].initialise(i,fenetre,DX,DY);
        colonies[i].setCView(cviews[i]);
        connexions[i].c = colonies + i;
        cviews[i].connect(&connexions[i]);
        QObject::connect(pause, SIGNAL(clicked()),&connexions[i], SLOT(pause()));
        QObject::connect(stop, SIGNAL(clicked()),&connexions[i], SLOT(stop()));
        QObject::connect(close, SIGNAL(clicked()),&connexions[i], SLOT(stop()));
        colonies[i].plot(0);
    }

    fenetre->show();
    fenetre->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            fenetre->size(),
            a->desktop()->availableGeometry()
        )
    );
    fenetre->setFixedSize(fenetre->size());

    QObject::connect(close, SIGNAL(clicked()), a, SLOT(quit()));
    QObject::connect(close, SIGNAL(clicked()),global, SLOT(quitfenetre()));

    QEventLoop loop;
    QObject::connect(run, SIGNAL(clicked()), &loop, SLOT(quit()));
    QObject::connect(stop, SIGNAL(clicked()), &loop, SLOT(quit()));
    QObject::connect(close, SIGNAL(clicked()), &loop, SLOT(quit()));

    loop.exec();
    run->setDisabled(true);
    run->setStyleSheet("QPushButton { font-size: 10pt; font-weight: bold; color: grey;}");


    /// Algorithme
    while(!isfinished(colonies,K))/// A changer
    {
        //#pragma omp parallel for
        for(int i=0;i<K;i++){
            colonies[i].colonie_steps(1);
            colonies[i].setCView(cviews[i]);
            colonies[i].plot(8);
        }
        a->processEvents();
    }

    /// Affichage Final
    for(int i=0;i<K;i++){
        colonies[i].write_result("Solution" + QString::number(i+1) + "_" + date.toString("dd-MM-yyyy") + "_"+time.toString("hh-mm-ss"));
        colonies[i].setOptions(false,true);
        colonies[i].setCView(cviews[i]);
        colonies[i].plot(1);
        //a->processEvents();
    }

    stop->setEnabled(false);
    stop->setStyleSheet("QPushButton { font-size: 10pt; font-weight: bold; color: grey;}");

    if(!fenetre->isVisible())a->quit();

    a->exec();
    delete fenetre;
    a->quit();
    return 0;
}
