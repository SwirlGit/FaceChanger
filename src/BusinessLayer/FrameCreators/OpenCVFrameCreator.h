#ifndef OPENCVFRAMECREATOR_H
#define OPENCVFRAMECREATOR_H

#include "BusinessLayer/FrameCreator.h"

class QImage;
namespace cv
{
class VideoCapture;
}

namespace BusinessLayer {

/**
 * @brief Класс получающий изображения с помощью OpenCV
 */
class OpenCVFrameCreator : public IFrameCreator
{
    Q_OBJECT

public:
    explicit OpenCVFrameCreator(int cameraIndex, int fps = 30, QObject *parent = nullptr);
    ~OpenCVFrameCreator() override;

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

#endif // OPENCVFRAMECREATOR_H
