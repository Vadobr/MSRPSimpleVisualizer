#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <qpainterpath.h>
#include <qfontmetrics.h>

#include <vector>
#include <string>

struct Point {

    double x;
    double y;

};

class GraphWidget :
    public QWidget
{

private:

    std::vector <std::string> names;
    std::vector <std::vector<double>> intesities;
    

    std::vector <Point> coordinates;

    Point centre;

public:

    void paintEvent(QPaintEvent* event) override;

public:

    void Fill(std::vector<std::string> names, std::vector<std::vector<double>> intensities);

private:

    void CalculateVerticesCoordinates();

private:

    bool IsRedoCurve(QPointF p0, QPointF p1, QPointF p2, QPointF p3);

    qreal calculateTriangleArea(const QPointF& p1, const QPointF& p2, const QPointF& p3);

    void drawArrowhead(QPainter& painter, const QPointF& p2, const QPointF& p3);

};

