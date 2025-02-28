#include "GraphicsWidgetClass.h"

void GraphicsWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    paintBackground(painter);
    
    paintGraphics(painter);

    paintLabels(painter);

}

void GraphicsWidget::paintBackground(QPainter& painter)
{

    painter.setFont(QFont("Consolas", 8));

    // Встановлюємо колір та товщину ліній для координатної сітки

    int countRows = 0;

    int countColumns = 0;

    int x;
    // Малюємо вертикальні лінії координатної сітки
    for (x = 0; x <= width(); x += cellWidth) {

        painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));

        painter.drawLine(x, 0, x, height() * 7. / 8.);

        countColumns++;

    }

    countColumns -= 3;

    x -= cellWidth;

    int y;
    // Малюємо горизонтальні лінії координатної сітки
    for (y = 0; y <= height() * 7. / 8.; y += cellWidth) {

        painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));

        painter.drawLine(0, y, width(), y);

        countRows++;
    }

    //countRows -= 1;

    countRows -= 2;

    y -= cellWidth;

    for (int y1 = cellWidth; y1 <= height() * 7. / 8.; y1 += cellWidth) {

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

        std::string str = std::to_string(1. - 1. / countRows * (y1 / cellWidth - 1));

        str.resize(4);

        painter.drawText(QRect(0, y1 - cellWidth, cellWidth - 2, cellWidth - 2), Qt::AlignBottom | Qt::AlignRight, str.c_str());

    }

    double timeScale = 0;

    for (int x1 = cellWidth * 3; x1 <= width(); x1 += cellWidth) {

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

        timeScale = 1. / countColumns * (x1 / cellWidth - 2);

        double curTime = (endTime - beginTime) * timeScale + beginTime;

        std::string str = std::to_string(curTime);

        str.resize(4);

        painter.drawText(QRect(x1 - cellWidth * 2, y, cellWidth - 2, cellWidth - 2), Qt::AlignTop | Qt::AlignRight, str.c_str());

    }

    // Встановлюємо колір та товщину лінії для осей координат
    painter.setPen(QPen(Qt::black, 2));

    // Малюємо вертикальну вісь координат
    painter.drawLine(cellWidth, 0, cellWidth, height());

    // Малюємо горизонтальну вісь координат
    painter.drawLine(0, y, width(), y);

    painter.setFont(QFont("Consolas", 10));

    painter.drawText(QRect(cellWidth, 0, cellWidth, cellWidth), Qt::AlignHCenter | Qt::AlignCenter, "Pi(t)");

    painter.drawText(QRect(x - cellWidth / 2, y, cellWidth, cellWidth), Qt::AlignHCenter | Qt::AlignCenter, "t");

    ///

    endX = x;

    endY = y;



}

void GraphicsWidget::paintGraphics(QPainter& painter)
{

    colors = generateContrastingColors(results[0].size());

    double dx = this->endX - cellWidth * 2;

    dx /= results.size() - 1;

    for(int i(0); i < results[0].size(); i++)
    {

        painter.setPen(QColor(colors[i]));

        QPainterPath path;

        path.moveTo(cellWidth, endY - results[0][i] * (endY - cellWidth));

        for (int j(1); j < results.size(); j++) {

            path.lineTo(cellWidth + dx * j, endY - results[j][i] * (endY - cellWidth));

        }

        painter.drawPath(path);

    }

}

void GraphicsWidget::paintLabels(QPainter& painter)
{

    painter.setFont(QFont("Consolas", 12));

    std::string str;

    for (int i(0); i < this->results[0].size(); i++) {

        str = "P(";
        str += std::to_string(i);
        str += ")";

        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));

        painter.drawText(QRect(((i+1)*2 + 0)*cellWidth, this->endY + cellWidth / 2, cellWidth, cellWidth), Qt::AlignBottom | Qt::AlignRight, str.c_str());

        {

            painter.setPen(QPen(QColor(colors[i]), 3));

            QPainterPath path;

            path.moveTo(((i + 1) * 2 + 1) * cellWidth + 1, this->endY + cellWidth * 5 / 4);

            for (int j(1); j < results.size(); j++) {

                path.lineTo(((i + 1) * 2 + 2) * cellWidth + 2, this->endY + cellWidth * 5 / 4);

            }

            painter.drawPath(path);

        }

    }

}

void GraphicsWidget::FillTime(double beginTime, double endTime)
{

    this->beginTime = beginTime;
    this->endTime = endTime;

}

void GraphicsWidget::FillResults(const std::vector<std::vector<double>>& results)
{

    this->results = results;

}

std::vector<QColor> GraphicsWidget::generateContrastingColors(int n)
{
    std::vector<QColor> colors;

    // Генеруємо кольори з різними відтінками
    for (int i = 0; i < n; ++i) {
        qreal hue = static_cast<qreal>(i) / n;
        qreal saturation = 1.0;
        qreal lightness = 0.5;

        // Створюємо QColor за вказаними значеннями HSL
        QColor color;
        color.setHslF(hue, saturation, lightness);

        // Додаємо кольор до списку
        colors.push_back(color);
    }

    return colors;
}

