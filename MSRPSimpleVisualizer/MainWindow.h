#pragma once

#include <QtWidgets/QMainWindow>
#include <qfile.h>
#include <qxmlstream.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <qabstractbutton.h>
#include <qcombobox.h>
#include <qmovie.h>
#include <qtimer.h>
#include <qurl.h>
#include <qtemporaryfile.h>
#include <qfiledialog.h>
#include <qdesktopservices.h>

#include "clickabkemenu.h"

#include "StartupConfig.h"


#ifdef _DEVELOP_ON_ANDROID_
#include "ui_MainWindowAndroid.h"
#else
#include "ui_MainWindow.h"
#endif

#include "MatrixViewModel.h"
#include "MainThreadWorkloadObsercerClass.h"
#include "GraphWidgetClass.h"

#include <thread>
#include <string>
#include <memory>
#include <map>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    
    MainThreadWorkloadObsercer* workloadObserver;

    QButtonGroup* radioButtonGroup;

    MatrixViewModel* matrixViewModel;


    Ui::MainWindowClass ui;


    std::map <QString, QString> GetLocaleTable(const std::string& locale);

    void SetLocale(const std::string& locale);

private slots:

    void StartLoading();

    void EndLoading();

private:

    QTimer* redrawTimer;

    void RedrawTimerTick();

signals:

    void ChangeFocusedCellText(QString);

private slots:

    void FunctionTextChanged();

    void LanguageChange();

    void StatesCountChanged();

private slots:

    void MatrixTabChoosen();

    void ResultsTabChoosen();

    void GraphicsTabChoosen();
    
    void GraphTabChoosen();

private:

    void StepCountChanged(const int& value);

    void BeginTimeChanged(const double& value);

    void EndTimeChanged(const double& value);

protected:

    void resizeEvent(QResizeEvent* event) override;

public slots:

    void FocusedNewCell();

    void RecountTransitions();

private slots:

    void ChangeMod();

private slots:

    void onSaveGraph();

    void onSaveGraphics();

    void onSaveResults();

private slots:

    void onAbout();

};

