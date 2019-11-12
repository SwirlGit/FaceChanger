#ifndef FRAMECAPTURE_H
#define FRAMECAPTURE_H

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
class IFrameCapture : public QObject
{
    Q_OBJECT

public:
    explicit IFrameCapture(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IFrameCapture() = default;

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

} // namespace BusinessLayer

#endif // FRAMECAPTURE_H
