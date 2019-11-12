#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include <QVector>
#include <memory>

class QImage;
class QThread;
namespace BusinessLayer {
class IEffectImage;
class FaceImage;
class IFaceImageCreator;
class IFrameCapture;
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
     * @brief Инициализировать эффекты
     */
    void initEffects();

private slots:
    /**
     * @brief Обработка кадра с камеры
     */
    void processFrame(const QImage& frame);

    /**
     * @brief Установить текущий эффект
     */
    void setCurrentEffect(int index);

private:
    /**
     * @brief Представление приложения
     */
    std::unique_ptr<ViewLayer::ApplicationView> m_view;

    /**
     * @brief Эффекты приложения
     */
    QVector<BusinessLayer::IEffectImage*> m_effects;

    /**
     * @brief Текущий выбранный эффект
     */
    int m_currentEffect = 0;

    /**
     * @brief Определитель лица на фотографии
     */
    BusinessLayer::IFaceImageCreator* m_faceImageCreator = nullptr;

    /**
     * @brief Ресивер изображений
     */
    BusinessLayer::IFrameCapture* m_frameCapture = nullptr;

    /**
     * @brief Тред для ресивера изображений
     */
    QThread* m_frameCaptureThread = nullptr;
};

} // namespace ManagementLayer

#endif // APPLICATIONMANAGER_H
