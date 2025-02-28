
#include "MainWindow.h"
#include <QtWidgets/QApplication>

bool isGlobalStationary;

int rowPos, colPos;

class AdvancedCentralCell;

AdvancedCentralCell* focusedCell = nullptr;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
