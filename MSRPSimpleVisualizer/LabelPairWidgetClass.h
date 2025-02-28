#pragma once

#include "StartupConfig.h"

#include <qwidget.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qtextedit.h>

#include "AdvancedLabelClass.h"

class LabelPairWidget : public QWidget {

Q_OBJECT

protected:

	QHBoxLayout* layout;

	AdvancedLabel* leftLabel;

	AdvancedLabel* rightLabel;

public:

	virtual void SetStyles();

public:

	void SetSelectedStyle();

private:

	int row;

protected:

	void focusInEvent(QFocusEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;

private:

signals:

	void AlreadySelected(int row);

	void AlreadyUnselected(int row);

public:

	LabelPairWidget(const int& row);

	~LabelPairWidget();

public:

	void SetLeftText(std::string newText);

	void SetRightText(std::string newText);

};