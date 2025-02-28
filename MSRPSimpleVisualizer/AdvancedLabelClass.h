#pragma once

#include "StartupConfig.h"

#include <qlabel.h>
#include <qtextedit.h>

class AdvancedLabel : public QTextEdit {

	Q_OBJECT

private:

	int row;
	int column;

public:

	void SetStyles();

public:

	AdvancedLabel(const int& row, const int& column);

protected:

	void focusInEvent(QFocusEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;

signals:

	void AlreadySelected(int row, int column);

	void AlreadyUnselected(int row, int column);

signals:

	void focusIn(QFocusEvent* event);
	void focusOut(QFocusEvent* event);

};