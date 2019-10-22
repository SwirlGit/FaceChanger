#ifndef UIHELPER_H
#define UIHELPER_H

class QWidget;

/**
 * @brief Помощник в работе с UI
 */
class UIHelper
{
public:
    /**
     * @brief Обновить стиль для виджета
     */
    static void refreshStyleSheet(QWidget* widget);
};

#endif // UIHELPER_H
