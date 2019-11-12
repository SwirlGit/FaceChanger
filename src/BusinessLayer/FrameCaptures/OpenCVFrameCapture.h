#ifndef OPENCVFRAMECAPTURE_H
#define OPENCVFRAMECAPTURE_H

#include "BusinessLayer/FrameCapture.h"

class QImage;
namespace cv
{
class VideoCapture;
}

namespace BusinessLayer {

/**
 * @brief Класс получающий изображения с помощью OpenCV
 */
class OpenCVFrameCapture : public IFrameCapture
{
    Q_OBJECT

public:
    explicit OpenCVFrameCapture(int cameraIndex, int fps = 30, QObject *parent = nullptr);
    ~OpenCVFrameCapture() override;

public slots:
    /**
     * @brief Запустить получение изображений, следует запускать в другом потоке
     */
    void start() override final;

private:
    /**
     * @brief Указатель на класс работы с камерой
     */
    cv::VideoCapture* m_videoCapture = nullptr;

    /**
     * @brief Индекс камеры, с которой снимаем изображение
     */
    int m_cameraIndex;

    /**
     * @brief Задержка между получением кадров
     */
    qint64 m_captureTimeoutMs;
};

} // namespace BusinessLayer

#endif // OPENCVFRAMECAPTURE_H
