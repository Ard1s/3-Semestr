#include <QApplication>
#include "Sapper.h"
#include <QtWidgets>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Sapper sapper;
    sapper.setWindowTitle("Сапёр");
    sapper.show();
    return app.exec();
}
