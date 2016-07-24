#include "interface.h"
using namespace std;

bool ask_main_parameters(int& K,int& n,int& DX,int& DY)
{
    QWidget * fenetre0 = new QWidget();
    fenetre0->setStyleSheet("QPushButton { font-size: 10pt; background-color: lightgrey }");
    fenetre0->setWindowTitle("Problem generation");
    fenetre0->setFixedWidth(322);
    fenetre0->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
    QImage myImage;
    myImage.load("ants.png");

    QLabel * myLabel = new QLabel();
    myLabel->setPixmap(QPixmap::fromImage(myImage));

    QSpinBox * kbox = new QSpinBox;
    kbox->setRange(1,10);
    kbox->setValue(K_d);
    QSpinBox * nbox = new QSpinBox;
    nbox->setRange(10,300);
    nbox->setValue(N_d);
    QSpinBox * dxbox = new QSpinBox;
    dxbox->setRange(75,1000);
    dxbox->setValue(DX_d);
    QSpinBox * dybox = new QSpinBox;
    dybox->setRange(75,1000);
    dybox->setValue(DY_d);
    QCheckBox * load = new QCheckBox;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(myLabel);
    formLayout->addRow("Number of colonies : ", kbox);
    formLayout->addRow("Number of points : ", nbox);
    formLayout->addRow("Width : ", dxbox);
    formLayout->addRow("Height : ", dybox);
    formLayout->addRow("Load problem ", load);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(formLayout);

    QPushButton *boutonOk = new QPushButton("Next");
    layoutPrincipal->addWidget(boutonOk);

    fenetre0->setLayout(layoutPrincipal);
    fenetre0->show();

    QEventLoop loop;
    QObject::connect(boutonOk, SIGNAL(clicked()), &loop, SLOT(quit()));
    loop.exec();

    K = kbox->value();
    n = nbox->value();
    DX = dxbox->value();
    DY = dybox->value();
    bool res = load->checkState();

    delete myLabel;
    delete kbox;
    delete nbox;
    delete dxbox;
    delete dybox;
    delete load;
    delete formLayout;
    delete boutonOk;
    delete layoutPrincipal;
    delete fenetre0;

    return res;
}

void SetThings::reglage()
{
    c->ask_parameters();
    c->plot(8);
}

void SetThings::pause()
{
    c->setPause();
    c->plot(8);
}

void SetThings::stop()
{
    c->stop();
    c->plot(8);
}

void SetThings::quitfenetre()
{
    delete fenetre;
}

