#pragma once

#include "StartupConfig.h"

#include "SmartCell/SmartCellClass.h"

class AdvancedTableHeaderCell : public SmartCell {

Q_OBJECT

private:

	int column;

public:

	void SetStyleByState() override;

public:

	AdvancedTableHeaderCell(const int& column);

public:

	void focusInEvent(QFocusEvent* event) override;

	void focusOutEvent(QFocusEvent* event) override;

private:

signals:

	void AlreadySelected(int column);

	void AlreadyUnselected(int column);

};