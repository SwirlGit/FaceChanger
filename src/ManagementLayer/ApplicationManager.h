#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QVector>
#include <memory>

class QImage;
namespace BusinessLayer {
class EffectImage;
class FaceImage;
class IFaceImageCreator;
class IFrameCreator;
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
    void processFrame(const QImage& frame);

private:
    /**
     * @brief Представление приложения
     */
    std::unique_ptr<ViewLayer::ApplicationView> m_view;

    /**
     * @brief Эффекты приложения
     */
    QVector<BusinessLayer::EffectImage*> m_effects;

    /**
     * @brief Определитель лица на фотографии
     */
    BusinessLayer::IFaceImageCreator* m_faceImageCreator = nullptr;

    /**
     * @brief Получатель изображений
     */
    BusinessLayer::IFrameCreator* m_frameCreator = nullptr;
};

} // namespace ManagementLayer

#endif // APPLICATIONMANAGER_H
