#include "AdvancedResultTable.h"

AdvancedResultTable::AdvancedResultTable()
{

    SetObjectsSetsParameters();

    SetStyles();

    corner = new CornerLabelPairWidget();

    this->cornerGridLayout->addWidget(corner);

    SetCornerText();

}

void AdvancedResultTable::SetObjectsDependencies()
{

    this->setLayout(mainGridLayout);

    mainGridLayout->addWidget(cornerFunctionalWidget, 0, 0);
    mainGridLayout->addWidget(centralScrollArea, 1, 1);
    mainGridLayout->addWidget(leftScrollArea, 1, 0);
    mainGridLayout->addWidget(topScrollArea, 0, 1);

    cornerFunctionalWidget->setLayout(cornerFuntionalLayout);

    cornerFuntionalLayout->addWidget(cornerWidget);
    centralScrollArea->setWidget(centralWidget);
    leftScrollArea->setWidget(leftHatWidget);
    topScrollArea->setWidget(topHatWidget);

    cornerFuntionalLayout->addWidget(cornerWidget);

    cornerWidget->setLayout(cornerGridLayout);
    centralWidget->setLayout(centralGridLayout);
    leftHatWidget->setLayout(leftHatVerticalLayout);
    topHatWidget->setLayout(topHatHorizontalLayout);

    leftHatVerticalLayout->setAlignment(Qt::AlignCenter);
    cornerGridLayout->setAlignment(Qt::AlignLeft);

    cornerGridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    leftHatVerticalLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    topHatHorizontalLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    centralGridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    leftScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    leftScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    topScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    topScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    centralScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    centralScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    connect(
        centralScrollArea->verticalScrollBar(),
        &QScrollBar::valueChanged,
        this,
        [&](int value) {
            leftScrollArea->verticalScrollBar()->setValue(value);
        }
    );

    connect(
        centralScrollArea->horizontalScrollBar(),
        &QScrollBar::valueChanged,
        this,
        [&](int value) {
            topScrollArea->horizontalScrollBar()->setValue(value);
        }
    );

    leftScrollArea->verticalScrollBar()->setVisible(false);
    leftScrollArea->horizontalScrollBar()->setVisible(false);
    topScrollArea->verticalScrollBar()->setVisible(false);
    topScrollArea->horizontalScrollBar()->setVisible(false);

}

void AdvancedResultTable::SetObjectsSetsParameters()
{
    for (auto object : objectList) {



    }

    for (auto object : layoutList) {

        object->setContentsMargins(QMargins(0, 0, 0, 0));

        object->setSpacing(3);

    }

    for (auto object : widgetList) {

        object->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    }

    for (auto object : qurtersWidgetList) {

    }

    for (auto object : scrollAreaList) {

        object->setWidgetResizable(true);

        object->setFrameShape(QFrame::NoFrame);

    }



}

void AdvancedResultTable::SetStyles()
{

    QString style = R"(

        QScrollBar:vertical{
            
            border-radius: 7px;
            background-color: #726aa877;

            width: 15px;
        }
        
        QScrollBar:horizontal {
            
            border-radius: 7px;
            background-color: #726aa877;

            height: 15px;
        }

        QScrollBar::handle {

            border-radius: 7px;
            background-color: #726aa8;
            
            width: 10px;

        }

        QScrollBar::up-arrow, QScrollBar::down-arrow, QScrollBar::left-arrow, QScrollBar::right-arrow {
            background-color: #00000000;
        }

        QScrollBar::add-page, QScrollBar::sub-page {
            background-color: #00000000;
        }

        QScrollBar::add-line, QScrollBar::sub-line {
            background-color: #00000000;
        }

       )";

    this->setStyleSheet(style);

}

void AdvancedResultTable::PrepareAndGo()
{

    FillPureWidgets(12, 8);

    for (int i(0); i < 12; i++) {

        SetLeftHeaderText(std::to_string(i), std::to_string(0.5 * i), i);

        SetTopHeaderText(std::string("S") + std::to_string(i + 1), i);

        for (int j(0); j < 12; j++) {

            SetGridText("0,124321", i, j);

        }

    }


}

void AdvancedResultTable::FillPureWidgets(const int& rowsCount, const int& columnsCount)
{

    FreeMemory();

    leftHeaderSet.resize(rowsCount);

    for (int i(0); i < rowsCount; i++) {

        LabelPairWidget* labelPair = new LabelPairWidget(i);

        SetLeftSideWidget(labelPair, i);

        leftHeaderSet[i] = labelPair;

        connect(labelPair, &LabelPairWidget::AlreadySelected, this, &AdvancedResultTable::RowSelected);
        connect(labelPair, &LabelPairWidget::AlreadyUnselected, this, &AdvancedResultTable::RowUnselected);

        MainThreadWorkloadObsercer::ProcessEventsExcludeTimer();

    }

    topHeaderSet.resize(columnsCount);

    for (int i(0); i < columnsCount; i++)
    {
        AdvancedTableHeaderCell *tableHeaderCell = new AdvancedTableHeaderCell(i);

        SetTopSideWidget(tableHeaderCell, i);

        topHeaderSet[i] = tableHeaderCell;

        connect(tableHeaderCell, &AdvancedTableHeaderCell::AlreadySelected, this, &AdvancedResultTable::ColumnSelected);
        connect(tableHeaderCell, &AdvancedTableHeaderCell::AlreadyUnselected, this, &AdvancedResultTable::ColumnUnselected);

        MainThreadWorkloadObsercer::ProcessEventsExcludeTimer();

    }

    gridSet.resize(rowsCount);

    for (int i(0); i < rowsCount; i++) {

        gridSet[i].resize(columnsCount);

        for (int j(0); j < columnsCount; j++) {

            AdvancedLabel* element = new AdvancedLabel(i, j);

            SetCentralWidget(element, i, j);

            connect(element, &AdvancedLabel::AlreadySelected, this, &AdvancedResultTable::ElementSelected);
            connect(element, &AdvancedLabel::AlreadyUnselected, this, &AdvancedResultTable::ElementUnselected);

            gridSet[i][j] = element;

            MainThreadWorkloadObsercer::ProcessEventsExcludeTimer();

        }

    }

}

void AdvancedResultTable::ElementSelected(int row, int column)
{

    for (int i(0); i < row; i++) {

        for (int j(0); j < column; j++) {

            gridSet[row][j]->setStyleSheet("background-color: white;");
            gridSet[i][column]->setStyleSheet("background-color: white;");

        }

    }

    if (row == 0) {

        for (int j(0); j < column; j++) {

            gridSet[row][j]->setStyleSheet("background-color: white;");

        }

    }

    if (column == 0)
    {

        for (int j(0); j < row; j++) {

            gridSet[j][column]->setStyleSheet("background-color: white;");

        }

    }

    gridSet[row][column]->setStyleSheet("background-color: rgb(225, 225, 225); border: 4px solid rgb(170, 170, 170); border-radius: 3px");

    leftHeaderSet[row]->SetSelectedStyle();
    topHeaderSet[column]->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0000FF, stop:1 #FFFFFF);");



}

void AdvancedResultTable::ElementUnselected(int row, int column)
{

    for (int i(0); i < row; i++) {

        for (int j(0); j < column; j++) {

            gridSet[row][j]->SetStyles();
            gridSet[i][column]->SetStyles();

        }

    }

    if (row == 0) {

        for (int j(0); j < column; j++) {

            gridSet[row][j]->SetStyles();
        }

    }

    if (column == 0)
    {

        for (int j(0); j < row; j++) {

            gridSet[j][column]->SetStyles();

        }

    }

    gridSet[row][column]->SetStyles();

    leftHeaderSet[row]->SetStyles();
    topHeaderSet[column]->SetStyleByState();

}

void AdvancedResultTable::RowSelected(int row)
{
    leftHeaderSet[row]->SetSelectedStyle();

    for (int i(0); i < gridSet[row].size(); i++) {

        gridSet[row][i]->setStyleSheet("background-color: white;");

    }

}

void AdvancedResultTable::RowUnselected(int row)
{
    leftHeaderSet[row]->SetStyles();

    for (int i(0); i < gridSet[row].size(); i++) {

        gridSet[row][i]->SetStyles();

    }
}

void AdvancedResultTable::ColumnUnselected(int column)
{

    topHeaderSet[column]->SetStyleByState();

    for (int i(0); i < gridSet.size(); i++) {

        gridSet[i][column]->SetStyles();

    }

}

void AdvancedResultTable::ColumnSelected(int column)
{

    for (int i(0); i < gridSet.size(); i++) {

        gridSet[i][column]->setStyleSheet("background-color: white;");

    }
}

QWidget* AdvancedResultTable::returnCorner()
{
    return corner;
}

void AdvancedResultTable::FreeMemory()
{
    for (int i(0); i < topHeaderSet.size(); i++) {
        delete topHeaderSet[i];
    }

    for (int i(0); i < leftHeaderSet.size(); i++) {
        delete leftHeaderSet[i];
    }

    for (int i(0); i < gridSet.size(); i++) {
        
        for (int j(0); j < gridSet[i].size(); j++) {

            delete gridSet[i][j];

        }

    }

    topHeaderSet.clear();

    leftHeaderSet.clear();

    gridSet.clear();

}

void AdvancedResultTable::SetCornerText()
{

    corner->SetLeftText("STEP");

    corner->SetRightText("TIME");

}

void AdvancedResultTable::SetLeftHeaderText(std::string newLeftText, std::string newRightText, const int& row)
{

    leftHeaderSet[row]->SetLeftText(newLeftText);

    leftHeaderSet[row]->SetRightText(newRightText);

}

void AdvancedResultTable::SetTopHeaderText(std::string newText, const int& column)
{

    topHeaderSet[column]->setText(newText.c_str());

}

void AdvancedResultTable::SetGridText(std::string newText, const int& row, const int& column)
{

    gridSet[row][column]->setText(newText.c_str());

}

