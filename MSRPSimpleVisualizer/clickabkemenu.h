#pragma once
#include <qmenu.h>
class ClickableMenu : public QMenu {
    Q_OBJECT
public:
    using QMenu::QMenu;

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void menuClicked();
};

