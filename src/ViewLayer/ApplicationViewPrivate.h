#ifndef APPLICATION_VIEW_PRIVATE_H
#define APPLICATION_VIEW_PRIVATE_H

namespace ViewLayer
{
/**
 * @brief Данные главного предсталения приложения
 */
struct ApplicationViewPrivate
{
    ApplicationViewPrivate();
    ApplicationViewPrivate(const ApplicationViewPrivate&) = delete;
    void operator=(const ApplicationViewPrivate&) = delete;
};
}

#endif // APPLICATION_VIEW_PRIVATE_H
