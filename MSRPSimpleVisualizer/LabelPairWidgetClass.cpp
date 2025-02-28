#include "LabelPairWidgetClass.h"

void LabelPairWidget::SetStyles()
{

	if(row % 2)
	{

		rightLabel->setStyleSheet("background-color: rgb(222, 135, 135); color: black; border: 3px solid rgb(22, 23, 62);");

		leftLabel->setStyleSheet("background-color: rgb(204, 82, 82); color: black; border: 3px solid rgb(22, 23, 62);");

	}
	else
	{

		leftLabel->setStyleSheet("background-color: rgb(219, 94, 94); color: black; border: 3px solid rgb(22, 23, 62);");

		rightLabel->setStyleSheet("background-color: rgb(255, 151, 151); color: black; border: 3px solid rgb(22, 23, 62);");

	}
	
}

void LabelPairWidget::SetSelectedStyle()
{
	leftLabel->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff0000, stop:1 #ffbdbd);");

	rightLabel->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ffbdbd, stop:1 #ffffff);;");


}

void LabelPairWidget::focusInEvent(QFocusEvent* event)
{

	QWidget::focusInEvent(event);

	emit AlreadySelected(row);

}

void LabelPairWidget::focusOutEvent(QFocusEvent* event)
{

	QWidget::focusOutEvent(event);

	emit AlreadyUnselected(row);

}

LabelPairWidget::LabelPairWidget(const int& row)
{	

	this->row = row;

	layout = new QHBoxLayout(); 

	this->setLayout(layout);


	leftLabel = new AdvancedLabel(-1, -1);

	leftLabel->setText("-L");

	leftLabel->setReadOnly(true);


	rightLabel = new AdvancedLabel(-1, -1);
	
	rightLabel->setText("R-");

	rightLabel->setReadOnly(true);


	layout->addWidget(leftLabel);

	layout->addWidget(rightLabel);


	this->setFocusPolicy(Qt::ClickFocus);

	rightLabel->setFocusPolicy(Qt::ClickFocus);

	leftLabel->setFocusPolicy(Qt::ClickFocus);



	connect(leftLabel, &AdvancedLabel::focusIn, this, &LabelPairWidget::focusInEvent);

	connect(leftLabel, &AdvancedLabel::focusOut, this, &LabelPairWidget::focusOutEvent);

	connect(rightLabel, &AdvancedLabel::focusIn, this, &LabelPairWidget::focusInEvent);

	connect(rightLabel, &AdvancedLabel::focusOut, this, &LabelPairWidget::focusOutEvent);

#ifdef _DEVELOP_ON_ANDROID_

	leftLabel->setMinimumHeight(20);

	leftLabel->setMinimumWidth(60);

	leftLabel->setMaximumHeight(20);

	leftLabel->setMaximumWidth(60);



	rightLabel->setMinimumHeight(20);

	rightLabel->setMinimumWidth(60);

	rightLabel->setMaximumHeight(20);

	rightLabel->setMaximumWidth(60);

#else

	leftLabel->setMinimumHeight(30);

	leftLabel->setMinimumWidth(90);

	leftLabel->setMaximumHeight(30);

	leftLabel->setMaximumWidth(90);



	rightLabel->setMinimumHeight(30);

	rightLabel->setMinimumWidth(90);

	rightLabel->setMaximumHeight(30);

	rightLabel->setMaximumWidth(90);

#endif

	layout->setContentsMargins(QMargins(0, 0, 0, 0));

	SetStyles();


	this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

}	

LabelPairWidget::~LabelPairWidget()
{

	delete leftLabel;
	delete rightLabel;
	delete layout;

}

void LabelPairWidget::SetLeftText(std::string newText)
{
	leftLabel->setText(newText.c_str());
}

void LabelPairWidget::SetRightText(std::string newText)
{
	rightLabel->setText(newText.c_str());
}
