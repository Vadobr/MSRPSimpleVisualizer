#pragma once
#include "StartupConfig.h"

#include "SmartMatrixWidget/SmartMatrixWidgetClass.h"

#include "LabelPairWidgetClass.h"
#include "AdvancedLabelClass.h"
#include "CornerLabelPairWidget.h"
#include "AdvancedTableHeaderCellClass.h"
#include "MainThreadWorkloadObsercerClass.h"

#include <qcoreapplication.h>

class AdvancedResultTable : public SmartMatrix {

    Q_OBJECT

public:

	AdvancedResultTable();

private:


    void SetObjectsDependencies() override;

    void SetObjectsSetsParameters() override;

    void SetStyles() override;

public:

    void PrepareAndGo();

public:

    void FillPureWidgets(const int& rowsCount, const int& columnsCount);

protected slots:

    void ElementSelected(int row, int column);

    void ElementUnselected(int row, int column);

    void RowSelected(int row);

    void RowUnselected(int row);

    void ColumnUnselected(int column);

    void ColumnSelected(int column);

private:

    std::vector<std::vector <AdvancedLabel*>> gridSet;

    std::vector<LabelPairWidget*> leftHeaderSet;

    std::vector<AdvancedTableHeaderCell*> topHeaderSet;

    CornerLabelPairWidget* corner;

    QWidget* returnCorner();

    void FreeMemory();

public:

    void SetCornerText();

    void SetLeftHeaderText(std::string newLeftText, std::string newRightText, const int& row);

    void SetTopHeaderText(std::string newText, const int& column);

    void SetGridText(std::string newText, const int& row, const int& column);

};