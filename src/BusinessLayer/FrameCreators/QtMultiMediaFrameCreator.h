#ifndef QTMULTIMEDIAFRAMECREATOR_H
#define QTMULTIMEDIAFRAMECREATOR_H

#include "BusinessLayer/FrameCreator.h"
#include <QCamera>
class QCamera;
class QCameraImageCapture;
class QCameraInfo;
class QImage;
class QMediaRecorder;

namespace BusinessLayer {

class QtMultiMediaFrameCreator : public IFrameCreator
{
    Q_OBJECT

public:
    explicit QtMultiMediaFrameCreator(int fps, QObject *parent = nullptr);
    ~QtMultiMediaFrameCreator() override;

public slots:
    /**
     * @brief Запустить получение изображений, следует запускать в другом потоке
     */
    void start() override final;

private:
    /**
     * @brief Устновить используемую камеру
     */
    void setCamera(const QCameraInfo& cameraInfo);

    /**
     * @brief startCamera
     */
    void startCamera();

private slots:
    /**
     * @brief Обработать полученное изображение
     */
    void processCapturedImage(int requestId, const QImage& image);

    void captureReady(bool ready);

    void processStatus(QCamera::Status status);

private:
    /**
     * @brief Указатель на камеру
     */
    QCamera* m_camera = nullptr;

    /**
     * @brief Указатель на класс для захвата изображения
     */
    QCameraImageCapture* m_imageCapture = nullptr;

    /**
     * @brief Задержка между получением кадров
     */
    qint64 m_captureTimeoutMs;
};

} // namespace BusinessLayer

#endif // QTMULTIMEDIAFRAMECREATOR_H
