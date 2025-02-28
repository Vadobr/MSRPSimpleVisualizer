#include "GraphWidgetClass.h"

void GraphWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    this->CalculateVerticesCoordinates();

    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    painter.setRenderHint(QPainter::Antialiasing, true);
    

    const double width = 50;
    const double height = 50;

    const double curvesting = 50;    

    for (int i(0); i < coordinates.size(); i++) {

        for (int j(i+1); j < coordinates.size(); j++) {

            if (i == j)
                continue;


            if(this->intesities[i][j] > 0.0001)
            {

                QPainterPath path;

                QPointF p0(coordinates[i].x, coordinates[i].y);
                QPointF p3(coordinates[j].x, coordinates[j].y);


                QPointF p1(((p0.x() - p3.x()) * 2. / 3. + p3.x()), ((p0.y() - p3.y()) * 2. / 3. + p3.y()));
                QPointF p2(((p0.x() - p3.x()) * 1. / 3. + p3.x()), ((p0.y() - p3.y()) * 1. / 3. + p3.y()));

                {

                    Point NVec;

                    NVec.x = (p1.x());
                    NVec.y = (p1.y());


                    NVec.x = (NVec.x - centre.x);
                    NVec.y = (NVec.y - centre.y);

                    double len = std::sqrt(NVec.x * NVec.x + NVec.y * NVec.y);

                    NVec.x /= len;
                    NVec.y /= len;

                    len += curvesting;

                    //            QPointF p1(centre.x + NVec.x * len, centre.y + NVec.y * len);

                    p1.setX(centre.x + NVec.x * len);
                    p1.setY(centre.y + NVec.y * len);


                }

                {

                    Point NVec;

                    NVec.x = (p2.x());
                    NVec.y = (p2.y());


                    NVec.x = (NVec.x - centre.x);
                    NVec.y = (NVec.y - centre.y);

                    double len = std::sqrt(NVec.x * NVec.x + NVec.y * NVec.y);

                    NVec.x /= len;
                    NVec.y /= len;

                    len += curvesting;

                    //            QPointF p1(centre.x + NVec.x * len, centre.y + NVec.y * len);

                    p2.setX(centre.x + NVec.x * len);
                    p2.setY(centre.y + NVec.y * len);


                }

                if (IsRedoCurve(p0, p1, p2, p3)) {
                    p1.setX(p1.x() + curvesting);
                    p1.setY(p1.y() + curvesting);
                    p2.setX(p2.x() + curvesting);
                    p2.setY(p2.y() + curvesting);
                }

                path.moveTo(p0);
                path.cubicTo(p1, p2, p3);

                QBrush transBrush(QColor(0, 0, 0, 0));

                painter.setBrush(transBrush);
                painter.setPen(QPen(QColor(255, 46, 70), 2));

                painter.drawPath(path);

                QPointF arrowheadStart = path.pointAtPercent(0.85); // точка на 95% від початку кривої
                QPointF arrowheadEnd = path.pointAtPercent(1.0); // кінцева точка кривої

                drawArrowhead(painter, arrowheadStart, arrowheadEnd);

                arrowheadStart = path.pointAtPercent(0.7);

                QBrush brush(Qt::white, Qt::BrushStyle::SolidPattern);  // Білий фон тексту

                painter.setBrush(brush);

                painter.setPen(QPen(QColor(0, 0, 0, 0), 0));
              

                std::string str = std::to_string(intesities[i][j]).c_str();

                for (int i(str.size() - 1); i >= 0; i--) {

                    if (str[i] == '0') {
                        str.pop_back();
                    }
                    else {
                        break;
                    }

                }

                if (str[str.size() - 1] == '.')
                    str.pop_back();

                double textWidth = 12 * str.size();

                painter.drawRect(QRect(arrowheadStart.x() - 10, arrowheadStart.y() - 10, 20, 20));

                painter.setPen(QColor(176, 0, 20));
                painter.setFont(QFont("Consolas", 12));

                painter.drawText(QRect(arrowheadStart.x() - textWidth/2, arrowheadStart.y() - 10, textWidth, 20), Qt::AlignHCenter | Qt::AlignCenter, str.c_str());

            }
        
            if (this->intesities[j][i] > 0.0001)
            {

                QPainterPath path;

                QPointF p0(coordinates[j].x, coordinates[j].y);
                QPointF p3(coordinates[i].x, coordinates[i].y);


                QPointF p1(((p0.x() - p3.x()) * 2. / 3. + p3.x()), ((p0.y() - p3.y()) * 2. / 3. + p3.y()));
                QPointF p2(((p0.x() - p3.x()) * 1. / 3. + p3.x()), ((p0.y() - p3.y()) * 1. / 3. + p3.y()));

                {

                    Point NVec;

                    NVec.x = (p1.x());
                    NVec.y = (p1.y());


                    NVec.x = (NVec.x - centre.x);
                    NVec.y = (NVec.y - centre.y);

                    double len = std::sqrt(NVec.x * NVec.x + NVec.y * NVec.y);

                    NVec.x /= len;
                    NVec.y /= len;

                    len -= curvesting;

                    //            QPointF p1(centre.x + NVec.x * len, centre.y + NVec.y * len);

                    p1.setX(centre.x + NVec.x * len);
                    p1.setY(centre.y + NVec.y * len);


                }

                {

                    Point NVec;

                    NVec.x = (p2.x());
                    NVec.y = (p2.y());


                    NVec.x = (NVec.x - centre.x);
                    NVec.y = (NVec.y - centre.y);

                    double len = std::sqrt(NVec.x * NVec.x + NVec.y * NVec.y);

                    NVec.x /= len;
                    NVec.y /= len;

                    len -= curvesting;

                    //            QPointF p1(centre.x + NVec.x * len, centre.y + NVec.y * len);

                    p2.setX(centre.x + NVec.x * len);
                    p2.setY(centre.y + NVec.y * len);


                }

                if (IsRedoCurve(p0, p1, p2, p3)) {
                    p1.setX(p1.x() - curvesting);
                    p1.setY(p1.y() - curvesting);
                    p2.setX(p2.x() - curvesting);
                    p2.setY(p2.y() - curvesting);
                }

                path.moveTo(p0);
                path.cubicTo(p1, p2, p3);

                painter.drawPath(path);

                QPointF arrowheadStart = path.pointAtPercent(0.85); // точка на 95% від початку кривої
                QPointF arrowheadEnd = path.pointAtPercent(1.0); // кінцева точка кривої

                drawArrowhead(painter, arrowheadStart, arrowheadEnd);

                arrowheadStart = path.pointAtPercent(0.7);

                QBrush brush(Qt::white, Qt::BrushStyle::SolidPattern);  // Білий фон тексту

                painter.setBrush(brush);

                painter.setPen(QPen(QColor(0, 0, 0, 0), 0));


                std::string str = std::to_string(intesities[j][i]).c_str();

                for (int i(str.size() - 1); i >= 0; i--) {

                    if (str[i] == '0') {
                        str.pop_back();
                    }
                    else {
                        break;
                    }

                }

                if (str[str.size() - 1] == '.')
                    str.pop_back();

                double textWidth = 12 * str.size();

                painter.drawRect(QRect(arrowheadStart.x() - 10, arrowheadStart.y() - 10, 20, 20));

                painter.setPen(QColor(176, 0, 20));
                painter.setFont(QFont("Consolas", 12));

                painter.drawText(QRect(arrowheadStart.x() - textWidth / 2, arrowheadStart.y() - 10, textWidth, 20), Qt::AlignHCenter | Qt::AlignCenter, str.c_str());

            }

        }
        
    }

    painter.setBrush(QBrush(QColor(114, 106, 168), Qt::BrushStyle::SolidPattern));


    
    for (int i(0); i < coordinates.size(); i++) {

        painter.setPen(QColor(176, 0, 20));

        painter.drawEllipse(coordinates[i].x - width / 2, coordinates[i].y - height / 2, width, height);

        QPointF p0;

        {

            Point NVec;

            NVec.x = coordinates[i].x;
            NVec.y = coordinates[i].y;


            NVec.x = (NVec.x - centre.x);
            NVec.y = (NVec.y - centre.y);

            double len = std::sqrt(NVec.x * NVec.x + NVec.y * NVec.y);

            NVec.x /= len;
            NVec.y /= len;

            len += curvesting;

            //            QPointF p1(centre.x + NVec.x * len, centre.y + NVec.y * len);

            p0.setX(centre.x + NVec.x * len);
            p0.setY(centre.y + NVec.y * len);


        }

        painter.setPen(QColor(58, 41, 171));

        QRect textRect(p0.x() - width / 2 , p0.y() - height / 2, width, height);

        painter.setFont(QFont("Consolas", 12));

        painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignCenter, names[i].c_str());

    }



//    path.cubicTo(QPointF(100, 200))

}

void GraphWidget::Fill(std::vector<std::string> names, std::vector<std::vector<double>> intensities)
{
    this->names = names;
    this->intesities = intensities;

}

void GraphWidget::CalculateVerticesCoordinates()
{

    centre.x = this->width();
    centre.y = this->height();

    centre.x /= 2.;
    centre.y /= 2.;

    const double PI = 3.14159265358979323846;

    double radius = std::min(centre.x, centre.y);

    radius *= 2. / 3.;

    this->coordinates.clear();

    int SIZE = names.size();

    for (int i = 0; i < SIZE; ++i) {
        
        double angle = 2 * PI * i / double(SIZE);
        
        Point coord;

        coord.x = centre.x + radius * std::cos(angle);
        coord.y = centre.y + radius * std::sin(angle);

        this->coordinates.push_back(coord);
    }

}

bool GraphWidget::IsRedoCurve(QPointF p0, QPointF p1, QPointF p2, QPointF p3)
{
    // Визначаємо площі трикутників
    qreal area1 = calculateTriangleArea(p0, p1, p2);
    qreal area2 = calculateTriangleArea(p1, p2, p3);

    // Сума площ трікутників
    qreal totalArea = area1 + area2;

    // Якщо сума дорівнює нулю, то точки лежать на одній прямій
    return qFuzzyCompare(totalArea, 0.0);
}

qreal GraphWidget::calculateTriangleArea(const QPointF& p1, const QPointF& p2, const QPointF& p3)
{
    return 0.5 * ((p2.x() - p1.x()) * (p3.y() - p1.y()) - (p3.x() - p1.x()) * (p2.y() - p1.y()));
}

void GraphWidget::drawArrowhead(QPainter& painter, const QPointF& start, const QPointF& end) {

    QPolygonF arrowhead;
    qreal arrowheadSize = 10.0;

    // Визначаємо координати стрілки
    arrowhead << QPointF(0, 0) << QPointF(-arrowheadSize, -arrowheadSize)
        << QPointF(-arrowheadSize, arrowheadSize);

    // Повертаємо та переміщуємо стрілку на відрізку
    QPointF direction = end - start;
    qreal angle = qAtan2(direction.y(), direction.x());
    QTransform transform;
    transform.translate(start.x(), start.y());
    transform.rotateRadians(angle);
    arrowhead = transform.map(arrowhead);

    painter.setPen(QPen(QColor(255, 46, 70), 2));

    painter.setBrush(QBrush(QColor(255, 46, 70), Qt::BrushStyle::SolidPattern));

    // Малюємо стрілку
    painter.drawPolygon(arrowhead);

}
