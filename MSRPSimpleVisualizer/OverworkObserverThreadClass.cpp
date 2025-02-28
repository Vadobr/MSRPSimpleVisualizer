#include "OverworkObserverThreadClass.h"

OverworkObserver::OverworkObserver(std::chrono::high_resolution_clock::time_point* observedTimePoint, int* expectedDelay, QWidget* mainWindow)
{

	this->previousTimePoint = observedTimePoint;

	this->expectedDelay = expectedDelay;

	this->mainWindow = mainWindow;

}

void OverworkObserver::Tick()
{

	std::chrono::high_resolution_clock::time_point currentTimePoint = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = currentTimePoint - (*previousTimePoint);

	const char* startLoading = "StartLoading";

	if (duration.count() > (*expectedDelay) * 2) {

		QMetaObject::invokeMethod(mainWindow, "StartLoading");

	}
	else {

		QMetaObject::invokeMethod(mainWindow, "EndLoading");

	}

}

void OverworkObserver::StartTimer()
{

	timer = new QTimer(this);

	connect(timer, &QTimer::timeout, this, &OverworkObserver::Tick);

	timer->start((*expectedDelay));

}

void OverworkObserver::StartThread()
{
	this->StartTimer();
}
