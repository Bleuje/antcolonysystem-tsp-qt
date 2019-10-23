#include "interface.h"
using namespace std;

bool ask_main_parameters(int& K,int& n,int& DX,int& DY)
{
    QWidget * window0 = new QWidget();
    window0->setStyleSheet("QPushButton { font-size: 10pt; background-color: lightgrey }");
    window0->setWindowTitle("Problem generation");
    window0->setFixedWidth(322);
    window0->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
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

    window0->setLayout(layoutPrincipal);
    window0->show();

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
    delete window0;

    return res;
}

void SetThings::setting()
{
    c->ask_parameters();
    c->plot(1.0);
}

void SetThings::pause()
{
    c->set_pause();
    c->plot(1.0);
}

void SetThings::stop()
{
    c->stop();
    c->plot(1.0);
}

void SetThings::quit_window()
{
    delete window;
}

