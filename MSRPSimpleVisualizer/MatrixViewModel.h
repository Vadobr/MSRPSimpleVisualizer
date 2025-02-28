#pragma once
#include <qtableview.h>
#include <qstandarditemmodel.h>
#include <qtableview.h>
#include <qheaderview.h>
#include <qlabel.h>
#include <qabstractbutton.h>
#include <qobject.h>
#include <qt>
#include <qcoreapplication.h>
#include <qwidget.h>

#include <algorithm>
#include <string>
#include <vector>

#include "SmartMatrixWidget/SmartMatrixWidgetClass.h"
#include "TransitionsMatrix.h"
#include "MainThreadWorkloadObsercerClass.h"
#include "AdvancedSmartMatrix.h"
#include "AdvancedResultTable.h"
#include "GraphWidgetClass.h"
#include "GraphicsWidgetClass.h"

class MatrixViewModel : public QObject {

Q_OBJECT

private:

	int size;
	int capacity;

	bool isStationary;

	TransitionsMatrix model;

	AdvancedSmartMatrix* matrixView;

	AdvancedResultTable* tableView;

	GraphWidget* graphView;

	GraphicsWidget* graphicsView;


public:

	friend class MainWindow;

	MatrixViewModel(const int& N);

public:

	void Resize(const int& N);

public:

	SmartMatrix* GetMatrixView();

	TransitionsMatrix* GetModel();

	AdvancedResultTable* GetTableViewl();

	GraphWidget* GetGraphView();

	GraphicsWidget* GetGraphicsView();

	ProbabilityBar* GetProbabilityBar();

private:

	void ElementsViewToModel();

	void MatrixViewToModel();

public:

	void FillResultsTable();

	void FillGraph();

	void FillGraphics();

public:

	void Fee();

public slots:

	void Focused3();

public:

signals:

	void Changes();

	void MatrixViewHaveUnresolvedChanges();

	void GraphViewHaveUnresolvedChanges();

	void TableViewHaveUnresolvedChanges();

	void GraphicViewHaveUnresolvedChanges();

	void EquationsViewHaveUnresolvedChanges();

	void Focused4();

};