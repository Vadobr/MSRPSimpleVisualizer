#include "clickabkemenu.h"

void ClickableMenu::mousePressEvent(QMouseEvent* event)
{
    emit menuClicked();
    QMenu::mousePressEvent(event); 
}
