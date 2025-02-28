#include "CornerLabelPairWidget.h"

void CornerLabelPairWidget::SetStyles()
{

	leftLabel->setStyleSheet("background-color: rgb(183, 97, 183); color: black; border: 3px solid rgb(22, 23, 62);");

	rightLabel->setStyleSheet("background-color: rgb(216, 106, 200); color: black; border: 3px solid rgb(22, 23, 62);");

}

CornerLabelPairWidget::CornerLabelPairWidget() : LabelPairWidget(0)
{
	SetStyles();

}
