#include "MainWindow.h"

extern bool isGlobalStationary;

extern int rowPos;
extern int colPos;

extern AdvancedCentralCell* focusedCell;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

#ifdef _DEVELOP_ON_ANDROID_

    ui.EquetionsRadioButton->hide();
    ui.GraphicsRadioButton->hide();
    ui.GraphRadioButton->hide();

    this->resize(QSize(640 / 10 * 7, 960 / 10 * 7));

#else

    this->resize(QSize(500, 660));

#endif

    ui.menuAbout;
    
    this->SetLocale("en");

    matrixViewModel = new MatrixViewModel(ui.StatesCountSpinBox->value());

    // Add separator
    //{
    //    QFrame* separator = new QFrame;
    //    separator->setFrameShape(QFrame::HLine); // Горизонтальний розділювач
    //    separator->setFrameShadow(QFrame::Sunken); // Тінь розділювача
    //    ui.MatrixTabVerticalLayout->addWidget(separator);
    //}

#ifdef _DEVELOP_ON_ANDROID_

    ui.MatrixTabVerticalLayout->insertWidget(0, matrixViewModel->GetMatrixView(), 2, Qt::AlignCenter);


#else

    ui.MatrixTabVerticalLayout->insertWidget(4, matrixViewModel->GetMatrixView(), 2, Qt::AlignCenter);

#endif

    QList<QAction*> menuItems = ui.LanguageMenu->actions();


    for(auto item : menuItems)
        connect(item, &QAction::triggered, this, &MainWindow::LanguageChange);

    connect(ui.StatesCountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::StatesCountChanged);

    ui.MatrixTabWidget->show();
    ui.ResultsTabWidget->hide();
    ui.GraphicsTabWidget->hide();
    ui.GraphTabWidget->hide();
    ui.LoadingWidget->hide();
    ui.EquationsTabWidget->hide();

    connect(ui.MatrixRadioButton, &QRadioButton::toggled, this, &MainWindow::MatrixTabChoosen);
    connect(ui.ResultsRadioButton, &QRadioButton::toggled, this, &MainWindow::ResultsTabChoosen);
    connect(ui.GraphRadioButton, &QRadioButton::toggled, this, &MainWindow::GraphTabChoosen);
    connect(ui.GraphicsRadioButton, &QRadioButton::toggled, this, &MainWindow::GraphicsTabChoosen);

    QMovie* movie = new QMovie(":/MainWindow/Loading.gif");
    
    ui.LoadingGifLabel->setMovie(movie);

    movie->start();

    ui.ResultsTabWidget->layout()->addWidget(matrixViewModel->GetTableViewl());

//    workloadObserver = new MainThreadWorkloadObsercer(this);

    redrawTimer = nullptr;

    ui.EquetionsRadioButton->hide();

    connect(ui.StepsCountSpinBox, &QSpinBox::valueChanged, this, &MainWindow::StepCountChanged);

    connect(ui.BeginTimeSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::BeginTimeChanged);

    connect(ui.EndTimeSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::EndTimeChanged);

    ui.GraphWidgetLayout->addWidget(matrixViewModel->GetGraphView());

    ui.GraphicsLayout->addWidget(matrixViewModel->GetGraphicsView());

#ifdef _DEVELOP_ON_ANDROID_



#endif

    QWidget* widget = new QWidget();

//    widget->setStyleSheet("background-color: yellow");

    widget->setLayout(matrixViewModel->GetProbabilityBar());

    ui.BeginProbabilityLayout->addWidget(widget);

//

    connect(matrixViewModel, &MatrixViewModel::Changes, this, &MainWindow::RecountTransitions);

//



/////////////////////

    connect(ui.ModeComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::ChangeMod);
    connect(ui.IntensitiesComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::ChangeMod);

    ChangeMod();


    connect(this->matrixViewModel, &MatrixViewModel::Focused4, this, &MainWindow::FocusedNewCell);

    ////

    connect(this->ui.plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::FunctionTextChanged);

    connect(this, &MainWindow::ChangeFocusedCellText, focusedCell, &AdvancedCentralCell::NewTextFromNowhere);

    //////


    connect(this->ui.SaveGraphAction, &QAction::triggered, this, &MainWindow::onSaveGraph);

    connect(this->ui.SaveGraphicsAction, &QAction::triggered, this, &MainWindow::onSaveGraphics);

    connect(this->ui.SaveResultsActions, &QAction::triggered, this, &MainWindow::onSaveResults);

    connect(this->ui.menuAbout, &ClickableMenu::menuClicked, this, &MainWindow::onAbout);

}

MainWindow::~MainWindow()
{}

std::map <QString, QString> MainWindow::GetLocaleTable(const std::string& locale)
{

    QFile file(":/MainWindow/Localization.csv");

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    in.setEncoding(QStringConverter::Encoding::Utf8);

    QStringList foundColum;
    QStringList firstColum;

    QString line(u8"\u4FF0");

    QStringList fields;


    line = in.readLine();
    
    fields = line.split(';');

    int columNumber = 0;

    for (int i(0); i < fields.size(); i++) {
        if (fields[i].compare(locale.c_str()) == 0) {
            columNumber = i;
            break;
        }
    }

    if (columNumber == 0)
        return std::map<QString, QString>();

    while (!in.atEnd())
    {
        line = in.readLine();

        fields = line.split(';');

        if (fields.size() > columNumber)
        {
            foundColum.append(fields.at(columNumber));
            firstColum.append(fields.at(0));
        }
    }

    file.close();

    std::map <QString, QString> result;

    for (int i(0); i < firstColum.size(); i++) {
    
        result[firstColum[i]] = foundColum[i];

    }

    return result;
}

void MainWindow::SetLocale(const std::string & locale)
{

    std::map <QString, QString> localeMap = GetLocaleTable(locale);

    std::map <QObject*, QString> objectMap = {
        {ui.LanguageMenu, "language" },
        {ui.FileMenu, "file"},
        {ui.GraphicsRadioButton, "graphics"},
        {ui.GraphRadioButton, "graph"},
//        {ui.HelpMenu, "help"},
        {ui.IntensitiesLabel, "intens"},
        {ui.MatrixRadioButton, "matrix"},
        {ui.ModeLabel, "mode"},
        {ui.OpenAction, "open"},
        {ui.ResultsRadioButton, "results"},
        {ui.SaveAction, "save"},
        {ui.SaveAsAction, "saveAs"},
        {ui.SaveGraphAction, "saveGraph"},
        {ui.SaveGraphicsAction, "saveGraphics"},
        {ui.SaveResultsActions, "saveResults"},
        {ui.StatesCountLabel, "stateCount"},
        {ui.StepsCountLabel, "stepCount"},
        {ui.TimeLabel, "begFinTime"},
        {ui.TransitionsCountLabel, "transCount"},
        {ui.label_4, "begProbs"}
    };

    ui.ModeComboBox;

    std::vector <QAbstractButton*> buttonList = {
       
    };
    

    std::vector <QMenu*> menuList = {
        ui.LanguageMenu,
        ui.FileMenu
//        ui.HelpMenu
    };

    std::vector <QAction*> actionList = {
        ui.OpenAction,
        ui.SaveAction,
        ui.SaveAsAction,
        ui.SaveGraphAction,
        ui.SaveGraphicsAction,
        ui.SaveResultsActions,
    };

    std::vector <QLabel*> labelList = {
        ui.IntensitiesLabel,
        ui.ModeLabel,
        ui.StatesCountLabel,
        ui.StepsCountLabel,
        ui.TimeLabel,
        ui.TransitionsCountLabel,
        ui.label_4
    };

    std::vector <QRadioButton*> radioButtonList = {
        ui.GraphicsRadioButton, 
        ui.GraphRadioButton,
        ui.MatrixRadioButton, 
        ui.ResultsRadioButton
    };

    for (auto key : buttonList) {

        key->setText(localeMap[objectMap[key]]);

    }

    for (auto key : menuList) {

        key->setTitle(localeMap[objectMap[key]]);

    }

    for (auto key : actionList) {

        key->setText(localeMap[objectMap[key]]);

    }

    for (auto key : labelList) {

        key->setText(localeMap[objectMap[key]]);

    }

    for (auto key : radioButtonList) {

        key->setText(localeMap[objectMap[key]]);

    }
    
    ui.ModeComboBox->setItemText(0, localeMap["unstat"]);
    ui.ModeComboBox->setItemText(1, localeMap["stat"]);
    ui.IntensitiesComboBox->setItemText(0, localeMap["nonPerm"]);
    ui.IntensitiesComboBox->setItemText(1, localeMap["perm"]);

}

void MainWindow::StartLoading()
{

    this->ui.LoadingWidget->show();

    if (!redrawTimer)
    {
        redrawTimer = new QTimer(this);

        connect(redrawTimer, &QTimer::timeout, this, &MainWindow::RedrawTimerTick);

        redrawTimer->start(41);

    }

}

void MainWindow::EndLoading()
{

    if (redrawTimer) {
        redrawTimer->stop();

        delete redrawTimer;

        redrawTimer = nullptr;

    }

    this->ui.LoadingWidget->hide();

}

void MainWindow::RedrawTimerTick()
{

    this->repaint();

}

void MainWindow::StatesCountChanged()
{
//    ui.LoadingWidget->show();

    matrixViewModel->Resize(ui.StatesCountSpinBox->value());

//    ui.LoadingWidget->hide();

}

void MainWindow::MatrixTabChoosen()
{
    if (!ui.MatrixRadioButton->isChecked())
        return;

    ui.MatrixTabWidget->show();
    ui.ResultsTabWidget->hide();
    ui.GraphicsTabWidget->hide();
    ui.GraphTabWidget->hide();


#ifdef _DEVELOP_ON_ANDROID_

    ui.toolBox->show();

#else



#endif



}

void MainWindow::ResultsTabChoosen()
{ 
    
    if (!ui.ResultsRadioButton->isChecked())
        return;

    ui.MatrixTabWidget->hide();
    ui.GraphicsTabWidget->hide();
    ui.GraphTabWidget->hide();

    //matrixViewModel->GetModel()->SetTime(ui.BeginTimeSpinBox->value(), ui.EndTimeSpinBox->value());
    //matrixViewModel->GetModel()->SetStepCount(ui.StepsCountSpinBox->value());

    matrixViewModel->FillResultsTable();

    ui.ResultsTabWidget->show();

#ifdef _DEVELOP_ON_ANDROID_

    ui.toolBox->hide();

#else

    

#endif

}

void MainWindow::GraphicsTabChoosen()
{

    this->matrixViewModel->FillGraphics();

    ui.MatrixTabWidget->hide();
    ui.ResultsTabWidget->hide();
    ui.GraphicsTabWidget->show();
    ui.GraphTabWidget->hide();
}

void MainWindow::GraphTabChoosen()
{
    ui.MatrixTabWidget->hide();
    ui.ResultsTabWidget->hide();
    ui.GraphicsTabWidget->hide();
    ui.GraphTabWidget->show();

    matrixViewModel->FillGraph();

    ui.GraphTabWidget->repaint();
}

void MainWindow::StepCountChanged(const int& value)
{

    matrixViewModel->GetModel()->SetStepCount(value);

}

void MainWindow::BeginTimeChanged(const double& value)
{

    matrixViewModel->GetModel()->SetBeginTime(value);
}

void MainWindow::EndTimeChanged(const double& value)
{

    matrixViewModel->GetModel()->SetEndTime(value);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);

    // При зміні розмірів вікна перемальовуємо віджет
    repaint();
}

void MainWindow::ChangeMod()
{

    int a = this->ui.ModeComboBox->currentIndex();
    int b = this->ui.IntensitiesComboBox->currentIndex();

    int c;

    this->matrixViewModel->matrixView->ClearGrid();

    if (    a == 0   && 
            b == 0   ) 
    {

        // Неcтаціонарний непостійний

        isGlobalStationary = false;

        ui.functionWidget->show();
        ui.FunctionLine->show();
        
        matrixViewModel->matrixView->SetUnpermanently();

        c = 0;

        return;

    }

    if (    a == 1   && 
            b == 0   ) 
    {

        // Стаціонарний непостійний

        isGlobalStationary = true;

        ui.functionWidget->hide();
        ui.FunctionLine->hide();

        matrixViewModel->matrixView->SetUnpermanently();

        c = 1;

        return;

    }

    if (    a == 0   && 
            b == 1   ) 
    {

        // Нетаціонарний постійний

        isGlobalStationary = false;

        matrixViewModel->matrixView->SetPermanently();

        ui.functionWidget->show();
        ui.FunctionLine->show();

        c = 2;

        return;

    }

    if (    a == 1   && 
            b == 1   ) 
    {

        // Стаціонарний постійний

        isGlobalStationary = true;

        ui.functionWidget->hide();
        ui.FunctionLine->hide();

        matrixViewModel->matrixView->SetPermanently();

        c = 3;

        return;

    }

}

void MainWindow::LanguageChange(){
    
    QAction* senderAction = qobject_cast<QAction*>(sender());
    if (senderAction) {
      
        if (senderAction == ui.ActionUkrainian) 
        {
            SetLocale("ua");
        
        }else if(senderAction == ui.ActionEnglish) 
        {
            SetLocale("en");
        
        }        

    }

}

void MainWindow::RecountTransitions() {

    int result(0);

    for (int i(0); i < this->matrixViewModel->matrixView->size; i++) {

        for (int j(0); j < this->matrixViewModel->matrixView->size; j++) {

            QString str =  this->matrixViewModel->matrixView->gridCellArray[i][j]->GetText();

            if(str.isEmpty()){
            

            
            }
            else {

                result += 1;

            }

        }

    }

    this->ui.TransitionsCountSpinBox->setValue(result);


}

void MainWindow::onSaveGraph()
{

    GraphTabChoosen();

    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save As"),
        "",
        tr("PNG Files (*.png);;JPG Files (*.jpg)")
    );

    if (!fileName.isEmpty())
    {

        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly))
        {

            QPixmap pixmap(ui.GraphTabWidget->size());

            ui.GraphTabWidget->render(&pixmap);

            // Збереження зображення у файл
            if (!pixmap.save(fileName))
            {
                //qDebug() << "Failed to save the image.";
            }

            file.close();
        }
    }

}

void MainWindow::onSaveGraphics()
{

    GraphicsTabChoosen();

    QString fileName = QFileDialog::getSaveFileName(
        this,
        tr("Save As"),
        "",
        tr("PNG Files (*.png);;JPG Files (*.jpg)")
    );

    if (!fileName.isEmpty())
    {

        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly))
        {
            
            QPixmap pixmap(ui.GraphicsTabWidget->size());
           
            ui.GraphicsTabWidget->render(&pixmap);

            // Збереження зображення у файл
            if (!pixmap.save(fileName))
            {
                //qDebug() << "Failed to save the image.";
            }

            file.close();
        }
    }

}

void MainWindow::onSaveResults()
{

    ResultsTabChoosen();

    std::vector<double> beginProbabilities = this->matrixViewModel->matrixView->GetProbablilityBar()->GetVector(this->matrixViewModel->model.Size());

    auto vec = this->matrixViewModel->model.SolveAsKolmagorovsEquation(beginProbabilities);

    QString fileName = QFileDialog::getSaveFileName(
        this, 
        tr("Save As"), 
        "",
        tr("CSV Files (*.csv);;Text Files (*.txt)")
    );

    if (!fileName.isEmpty())
    {

        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            
            out << "STEP;TIME";

            for (int i(0); i < this->matrixViewModel->model.Size(); i++) {
                out << ";" << this->matrixViewModel->model.GetVerticeName(i).c_str();
            }

//            out << "Sample text";  
  
            out << "\n";

            for (int i(0); i < vec.size(); i++) {

//                tableView->SetLeftHeaderText(std::to_string(i), std::to_string(i * this->model.GetDeltaTime()), i);

                out << i << ";" << i * this->matrixViewModel->model.GetDeltaTime();

                for (int j(0); j < vec[i].size(); j++) {

//                    tableView->SetGridText(std::to_string(vec[i][j]), i, j);

                    out << ";" << vec[i][j];

                }

                out << "\n";

            }


            file.close();
        }
    }

}

void MainWindow::onAbout()
{

    QFile file(":/MainWindow/Info.html");
    if (!file.open(QIODevice::ReadOnly)) return;

    // Створюємо тимчасовий файл із правильним розширенням
    QFile tempFile("info.html");
    if (tempFile.open(QIODevice::WriteOnly)) {

        tempFile.write(file.readAll());
        tempFile.flush();
        tempFile.close(); // Закриваємо, щоб ОС могла його прочитати

        QDesktopServices::openUrl(QUrl::fromLocalFile(tempFile.fileName()));
    }

}

void MainWindow::FocusedNewCell() {

    {

        std::string str = "";

        str += std::to_string(rowPos);

        str += std::to_string(colPos);

        this->ui.label_3->setText(str.c_str());

    }

    if(focusedCell)
        ui.plainTextEdit->setPlainText(focusedCell->toPlainText());

}

void MainWindow::FunctionTextChanged() {

    if (!focusedCell)
        return;

    if(focusedCell->toPlainText().compare(ui.plainTextEdit->toPlainText()))
        focusedCell->setText(ui.plainTextEdit->toPlainText());

}