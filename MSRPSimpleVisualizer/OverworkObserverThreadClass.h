#pragma once

#include <qwidget.h>
#include <qobject.h>
#include <qtimer.h>
#include <qmetaobject.h>
#include <qcoreapplication.h>

#include <chrono>

class MainWindow;

class OverworkObserver : public QObject 
{
Q_OBJECT
public:

    OverworkObserver(std::chrono::high_resolution_clock::time_point* observedTimePoint, int* expectedDelay, QWidget* mainWindow);

private:

    QWidget* mainWindow;

    QTimer* timer;

    std::chrono::high_resolution_clock::time_point* previousTimePoint;

    int* expectedDelay;

private:

    void Tick();

    void StartTimer();

public:

    void StartThread();


};