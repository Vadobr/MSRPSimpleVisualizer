#include "MainThreadWorkloadObsercerClass.h"

QTimer* MainThreadWorkloadObsercer::timer = nullptr;

MainThreadWorkloadObsercer::MainThreadWorkloadObsercer(QWidget* mainWindow)
{

	this->delayMilliseconds = 200;

	previousTimePoint = new std::chrono::high_resolution_clock::time_point();

	(*previousTimePoint) = std::chrono::high_resolution_clock::now();

	StartTimer();

	StartOverworkObserverThread(mainWindow);

}

void MainThreadWorkloadObsercer::StartTimer()
{

	if(timer == nullptr)
		timer = new QTimer();

	connect(timer, &QTimer::timeout, this, &MainThreadWorkloadObsercer::Tick);

	timer->start(delayMilliseconds);

}

void MainThreadWorkloadObsercer::Tick()
{

	(*previousTimePoint) = std::chrono::high_resolution_clock::now();

}

void MainThreadWorkloadObsercer::StartOverworkObserverThread(QWidget* mainWindow)
{

	this->overworkObserverObject = new OverworkObserver(this->previousTimePoint, &(this->delayMilliseconds), mainWindow);

	overworkObserverThread = new QThread();

	auto b = QThread::currentThreadId();

	overworkObserverObject->moveToThread(overworkObserverThread);

	connect(overworkObserverThread, &QThread::started, overworkObserverObject, &OverworkObserver::StartThread);

	overworkObserverThread->start();

}

void MainThreadWorkloadObsercer::ProcessEventsExcludeTimer()
{
	if (timer) {
	
		timer->blockSignals(true);

		QCoreApplication::processEvents();

		timer->blockSignals(false);
	
	}
}
