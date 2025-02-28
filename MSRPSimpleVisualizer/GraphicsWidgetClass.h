#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <qpainterpath.h>

#include <string>

class GraphicsWidget :
    public QWidget
{

private:

    int cellWidth = 40;

    double beginTime;
    double endTime;

    int endX;
    int endY;

    std::vector <std::vector<double>> results;

    std::vector<QColor> colors;

protected:

    void paintEvent(QPaintEvent* event) override;

    void paintBackground(QPainter& painter);

    void paintGraphics(QPainter& painter);

    void paintLabels(QPainter& painter);

public:

    void FillTime(double beginTime, double endTime);

    void FillResults(const std::vector <std::vector<double>>& results);

private:

    std::vector<QColor> generateContrastingColors(int n);

};

