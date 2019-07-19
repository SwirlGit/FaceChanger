#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QVector>
#include <memory>

namespace BusinessLayer {
class EffectImage;
class FaceImage;
}

namespace ViewLayer {
class ApplicationView;
}

namespace ManagementLayer
{
/**
 * @brief Менеджер приложения
 */
class ApplicationManager : public QObject
{
    Q_OBJECT

public:
    explicit ApplicationManager(QObject* parent = nullptr);
    ~ApplicationManager();

    /**
     * @brief Получить представление, которым управляем
     */
    QWidget* view() const;

    /**
     * @brief Запустить выполнение приложения
     */
    void exec();

private:
    /**
     * @brief Обработка кадра с камеры
     */
    void processFrame();

private:
    /**
     * @brief Представление приложения
     */
    std::unique_ptr<ViewLayer::ApplicationView> m_view;

    /**
     * @brief Эффекты приложения
     */
    QVector<BusinessLayer::EffectImage*> m_effects;
};

} // namespace ManagementLayer

#endif // APPLICATIONMANAGER_H
