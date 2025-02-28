#include "AdvancedTableHeaderCellClass.h"

void AdvancedTableHeaderCell::SetStyleByState()
{

    CorrectText();

    if (this->selectionState == SelectionState::unselected) {
                
        if (column % 2) 
        {
            this->setStyleSheet("border: 3px solid rgb(22, 23, 62); border-radius: 0px; background-color: rgb(137, 172, 204);");
        }else
        {
            this->setStyleSheet("border: 3px solid rgb(22, 23, 62); border-radius: 0px; background-color: rgb(155, 194, 230);");
        }
        
                
        this->setReadOnly(true);
        auto font = this->font();
        font.setBold(false);
        this->setFont(font);
    }
    else if (this->selectionState == SelectionState::preselected) {

        if (column % 2)
        {
            this->setStyleSheet("border: 0px solid rgb(22, 23, 62); border-radius: 2px; background-color: rgb(137, 172, 204);");
        }
        else
        {
            this->setStyleSheet("border: 0px solid rgb(22, 23, 62); border-radius: 2px; background-color: rgb(155, 194, 230);");
        }
        
        
        
        this->setReadOnly(true);
        auto font = this->font();
        font.setBold(true);
        this->setFont(font);
    }
    else if (this->selectionState == SelectionState::selected) {

        this->setStyleSheet("border: 3px solid rgb(22, 23, 62); border-radius: 10px; background-color: white;");
        
        this->setReadOnly(false);
        auto font = this->font();
        font.setBold(true);
        this->setFont(font);
        this->moveCursor(QTextCursor::End);
    }
}
AdvancedTableHeaderCell::AdvancedTableHeaderCell(const int& column)
{

    this->column = column;

    SetStyleByState();

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

    QFont font;
    font.setFamily("Consolas");
    font.setPointSize(12);

    this->setFont(font);

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QTextOption textOption = this->document()->defaultTextOption();
    textOption.setWrapMode(QTextOption::NoWrap);

    textOption.setAlignment(Qt::AlignCenter);

    this->document()->setDefaultTextOption(textOption);

}

void AdvancedTableHeaderCell::focusInEvent(QFocusEvent* event)
{

    SmartCell::focusInEvent(event);

    emit AlreadySelected(column);

}

void AdvancedTableHeaderCell::focusOutEvent(QFocusEvent* event)
{

    SmartCell::focusOutEvent(event);

    emit AlreadyUnselected(column);

}
