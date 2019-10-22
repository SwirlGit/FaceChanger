#include "UIHelper.h"

#include <QWidget>

void UIHelper::refreshStyleSheet(QWidget *widget)
{
    if (widget == nullptr) {
        return;
    }

    const QString sourceStyleSheet = widget->styleSheet();
    widget->setStyleSheet(" ");
    widget->setStyleSheet(sourceStyleSheet);
}
