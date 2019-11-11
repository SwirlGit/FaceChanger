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
    explicit IFrameCreator(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~IFrameCreator() = default;

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

#endif // FRAMECREATOR_H
