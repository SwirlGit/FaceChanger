#ifndef FRAMECREATOR_H
#define FRAMECREATOR_H

#include <QObject>

namespace BusinessLayer {

class IFrameCreator : public QObject
{
    Q_OBJECT

public:
    explicit IFrameCreator(QObject* parent = nullptr);

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

class OpenCVFrameCreator : public IFrameCreator
{
public:
    explicit OpenCVFrameCreator(QObject *parent = 0);

    /**
     * @brief Запустить получение изображений, следует запускать в другом потоке
     */
    void start() override final;
};

} // namespace BusinessLayer

#endif // FRAMECREATOR_H
