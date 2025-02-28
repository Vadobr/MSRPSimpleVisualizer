#include "MatrixViewModel.h"

MatrixViewModel::MatrixViewModel(const int& N)
{

    isStationary = true;

    size = 0;
    capacity = 0;

    tableView = new AdvancedResultTable();

    matrixView = new AdvancedSmartMatrix();

    graphView = new GraphWidget();

    graphicsView = new GraphicsWidget();

    connect(matrixView, &AdvancedSmartMatrix::Amend, this, &MatrixViewModel::MatrixViewToModel);

    connect(matrixView, &AdvancedSmartMatrix::Focused2, this, &MatrixViewModel::Focused3);

    Resize(N);

}

void MatrixViewModel::Resize(const int& N)
{

    model.Resize(N);
    
    matrixView->Resize(N);

    size = N;

}

SmartMatrix* MatrixViewModel::GetMatrixView()
{
    return matrixView;
}

void MatrixViewModel::ElementsViewToModel()
{

    double doubleRlement;

    std::string strElement;

    for (int i(0); i < size; i++) {
        for (int j(0); j < size; j++) {

            strElement = matrixView->GetElementAsTextEditText(i, j);

            std::replace(strElement.begin(), strElement.end(), ',', '.');

            if (strElement == "")
            {
                doubleRlement = 0;
            }
            else 
            {
                doubleRlement = std::stod(strElement.c_str());
            }


            model.SetIntensitiveElement(doubleRlement, i, j);

            model.SetFunctionOfElement(strElement, i, j);

        }
    }

}

void MatrixViewModel::MatrixViewToModel()
{
    
    bool isEnythingChanged = false;

    for (int i(0); i < size; i++) {

        if (matrixView->IsElementChanged(i + 1, 0))
        {

            isEnythingChanged = true;

            std::string text = matrixView->GetLeftHeaderAsTextEditText(i);

            model.SetVerticeName(text, i);

            matrixView->ApplyElementChanges(i + 1, 0);

        }

        //if (matrixView->IsElementChanged(0, i + 1))
        //{
        //    isEnythingChanged = true;
        //}

        for (int j(0); j < size; j++) {

            if (matrixView->IsElementChanged(i + 1, j + 1)) 
            {

                isEnythingChanged = true;

                std::string text = matrixView->GetElementAsTextEditText(i, j);

                std::replace(text.begin(), text.end(), ',', '.');

                model.SetIntensitiveElement(std::atof(text.c_str()), i, j);

                model.SetFunctionOfElement(text.c_str(), i, j);

                matrixView->ApplyElementChanges(i + 1, j + 1);

            }

        }

    }

    if (isEnythingChanged) {

        //emit MatrixViewHaveUnresolvedChanges();

        emit GraphViewHaveUnresolvedChanges();

        emit TableViewHaveUnresolvedChanges();

        emit GraphicViewHaveUnresolvedChanges();

        emit EquationsViewHaveUnresolvedChanges();

    }

    emit Changes();

}

TransitionsMatrix* MatrixViewModel::GetModel() {

    return &model;

}

AdvancedResultTable* MatrixViewModel::GetTableViewl()
{
    return tableView;
}

GraphWidget* MatrixViewModel::GetGraphView()
{
    return this->graphView;
}

GraphicsWidget* MatrixViewModel::GetGraphicsView()
{
    return this->graphicsView;
}

ProbabilityBar* MatrixViewModel::GetProbabilityBar()
{
    return this->matrixView->GetProbablilityBar();
}

void MatrixViewModel::FillResultsTable()
{

    std::vector<double> beginProbabilities = matrixView->GetProbablilityBar()->GetVector(model.Size());

    auto vec = this->model.SolveAsKolmagorovsEquation(beginProbabilities);

    QCoreApplication::processEvents();

    tableView->FillPureWidgets(vec.size(), size);

    for (int i(0); i < vec.size(); i++) {

        tableView->SetLeftHeaderText(std::to_string(i), std::to_string(i * this->model.GetDeltaTime()), i);

        for (int j(0); j < vec[i].size(); j++) {

            tableView->SetGridText(std::to_string(vec[i][j]), i, j);

            MainThreadWorkloadObsercer::ProcessEventsExcludeTimer();

        }

    }


    for (int i(0); i < vec[0].size(); i++) {

        tableView->SetTopHeaderText(model.GetVerticeName(i), i);

    }


}

void MatrixViewModel::FillGraph()
{

    std::vector <std::string> names(model.Size());

    for (int i(0); i < names.size(); i++) {

        names[i] = model.GetVerticeName(i);

    }

    std::vector<std::vector<double>> intensities;

    intensities.resize(names.size());

    for (int i(0); i < names.size(); i++) {
    
        intensities[i].resize(names.size());
    
    }

    for (int i(0); i < intensities.size(); i++) {
        for (int j(0); j < intensities[i].size(); j++) {

            intensities[i][j] = model.GeteIntensitie(i, j);

        }
    }

    graphView->Fill(names, intensities);

}

void MatrixViewModel::FillGraphics()
{

    std::vector<double> beginProbabilities = matrixView->GetProbablilityBar()->GetVector(model.Size());

    auto vec = this->model.SolveAsKolmagorovsEquation(beginProbabilities);

    this->graphicsView->FillTime(model.GetBeginTime(), model.GetEndTime());

    this->graphicsView->FillResults(model.SolveAsKolmagorovsEquation(beginProbabilities));

}

void Fee(){}

void MatrixViewModel::Focused3()
{

    emit Focused4();

}
