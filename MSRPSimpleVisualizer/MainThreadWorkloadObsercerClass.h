#pragma once

#include <qobject.h>
#include <qtimer.h>
#include <qthread.h>
#include <qcoreapplication.h>

#include <chrono>

#include "OverworkObserverThreadClass.h"

class MainWindow;

class MainThreadWorkloadObsercer : public QObject
{

Q_OBJECT
public:
	MainThreadWorkloadObsercer(QWidget* mainWindow);

private:

	std::chrono::high_resolution_clock::time_point* previousTimePoint;

	static QTimer *timer;

	int delayMilliseconds;

	QThread* overworkObserverThread;

	OverworkObserver* overworkObserverObject;


private:

	void StartTimer();

	void Tick();

	void StartOverworkObserverThread(QWidget* mainWindow);

public:

	static void ProcessEventsExcludeTimer();


};