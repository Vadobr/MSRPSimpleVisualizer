#include "AdvancedLabelClass.h"



void AdvancedLabel::SetStyles()
{

	if (column % 2 && row % 2)
	{
		this->setStyleSheet("background-color: rgb(180, 180, 180); color: black; border: 3px solid rgb(43, 45, 121);");
	}
	else if (column % 2)
	{
		this->setStyleSheet("background-color: rgb(210, 210, 210); color: black; border: 3px solid rgb(43, 45, 121);");
	}
	else if (row % 2)
	{
		this->setStyleSheet("background-color: rgb(195, 195, 195); color: black; border: 3px solid rgb(43, 45, 121);");
	}
	else
	{
		this->setStyleSheet("background-color: rgb(225, 225, 225); color: black; border: 3px solid rgb(43, 45, 121);");
	}

}

AdvancedLabel::AdvancedLabel(const int& row, const int& column)
{

	this->setReadOnly(true);

	this->row = row;
	this->column = column;

#ifdef _DEVELOP_ON_ANDROID_

	this->setMinimumHeight(20);

	this->setMinimumWidth(60);

	this->setMaximumHeight(20);

	this->setMaximumWidth(60);


#else

	this->setMinimumHeight(30);

	this->setMinimumWidth(90);

	this->setMaximumHeight(30);

	this->setMaximumWidth(90);


#endif



	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	SetStyles();

	this->setAlignment(Qt::AlignCenter);

	QTextOption textOption = this->document()->defaultTextOption();
	textOption.setWrapMode(QTextOption::NoWrap);

	textOption.setAlignment(Qt::AlignCenter);

	this->document()->setDefaultTextOption(textOption);

#ifdef _DEVELOP_ON_ANDROID_

	QFont font;
	font.setFamily("Consolas");
	font.setPointSize(8);

	this->setFont(font);

#else

	QFont font;
	font.setFamily("Consolas");
	font.setPointSize(12);

	this->setFont(font);

#endif



}

void AdvancedLabel::focusInEvent(QFocusEvent* event)
{

	QTextEdit::focusInEvent(event);

	emit AlreadySelected(row, column);

	emit focusIn(event);

}

void AdvancedLabel::focusOutEvent(QFocusEvent* event)
{

	QTextEdit::focusOutEvent(event);

	emit AlreadyUnselected(row, column);

	emit focusOut(event);

}

//void AdvancedLabel::AlreadyUnselected(int row, int column)
//{
//}
//
//void AdvancedLabel::AlreadySelected(int row, int column)
//{
//}
