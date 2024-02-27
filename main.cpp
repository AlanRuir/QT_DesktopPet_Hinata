#include "shimeji.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Shimeji w;
    w.show();

    return a.exec();
}
