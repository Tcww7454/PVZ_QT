#include "pvz.h"
#include<QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PVZ pvz;
    pvz.show();


    return app.exec();
}


