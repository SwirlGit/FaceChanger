#ifndef APPLICATION_VIEW_PRIVATE_H
#define APPLICATION_VIEW_PRIVATE_H

class ItemsSlider;
class QWidget;

namespace ViewLayer
{
/**
 * @brief Данные главного предсталения приложения
 */
struct ApplicationViewPrivate
{
    ApplicationViewPrivate(QWidget* parent = nullptr);
    ApplicationViewPrivate(const ApplicationViewPrivate&) = delete;
    void operator=(const ApplicationViewPrivate&) = delete;

    /**
     * @brief Установленные эффекты
     */
    ItemsSlider* effects = nullptr;
};
}

#endif // APPLICATION_VIEW_PRIVATE_H
