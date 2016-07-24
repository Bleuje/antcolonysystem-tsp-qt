#ifndef INTERFACE_H
#define INTERFACE_H

#include "colonie.h"

using namespace std;

class Colonie;

class SetThings : public QObject
{
    Q_OBJECT
public:
    Colonie * c;
    QWidget * fenetre;
public slots:
    void reglage();
    void pause();
    void stop();
    void quitfenetre();
};

bool ask_main_parameters(int& K,int& n,int& DX,int& DY);

#endif // INTERFACE_H
