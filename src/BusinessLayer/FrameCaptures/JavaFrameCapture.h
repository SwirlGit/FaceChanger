#ifndef JAVAFRAMECAPTURE_H
#define JAVAFRAMECAPTURE_H

#include "BusinessLayer/FrameCapture.h"

namespace BusinessLayer {

class JavaFrameCapture : public IFrameCapture
{
public:
    explicit JavaFrameCapture(QObject *parent = nullptr);
    ~JavaFrameCapture() override;

public slots:
    /**
     * @brief Запустить получение изображений, следует запускать в другом потоке
     */
    void start() override final;
};

} // namespace BusinessLayer

#endif // JAVAFRAMECAPTURE_H
