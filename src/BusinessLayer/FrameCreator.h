#ifndef FRAMECREATOR_H
#define FRAMECREATOR_H

#include <QObject>

class QImage;
namespace cv
{
class VideoCapture;
}

namespace BusinessLayer {

/**
 * @brief Интерфейс получения изображений
 */
class IFrameCreator : public QObject
{
    Q_OBJECT

public:
    explicit IFrameCreator(QObject* parent = nullptr);

public slots:
    /**
     * @brief Запустить получение изображений, следует запускать в другом потоке
     */
    virtual void start() = 0;

signals:
    /**
     * @brief Захвачено изображение
     */
    void frameCaptured(const QImage& frame);
};

/**
 * @brief Класс получающий изображения с помощью OpenCV
 */
class OpenCVFrameCreator : public IFrameCreator
{
    Q_OBJECT

public:
    explicit OpenCVFrameCreator(int cameraIndex, int fps = 30, QObject *parent = nullptr);
    ~OpenCVFrameCreator();

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

#endif // FRAMECREATOR_H
