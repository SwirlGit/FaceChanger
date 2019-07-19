#ifndef APPLICATION_VIEW_H
#define APPLICATION_VIEW_H

#include <QWidget>
#include <memory>

namespace ViewLayer
{
struct ApplicationViewPrivate;

/**
 * @brief Главное предсталение приложения
 */
class ApplicationView : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationView(QWidget* parent = nullptr);
    ~ApplicationView();

    /**
     * @brief Установить изображения эффектов
     */
    void setupEffectsIcons(const QVector<QImage>& effectsIcons);

    /**
     * @brief Обновить изображение на экране
     */
    void updateImage(const QImage& image);

signals:
    /**
     * @brief Изменился выбранный эффект
     */
    void currentEffectIndexChanged(int index);

private:
    /**
     * @brief Скрытая имплементация представления
     */
    std::unique_ptr<ApplicationViewPrivate> m_pimpl;
};
}

#endif // APPLICATION_VIEW_H

