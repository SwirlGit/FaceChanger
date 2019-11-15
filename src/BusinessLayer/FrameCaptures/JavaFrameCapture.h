#ifndef JAVAFRAMECAPTURE_H
#define JAVAFRAMECAPTURE_H

#include "BusinessLayer/FrameCapture.h"

class QAndroidJniObject;

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

private:
    /**
     * @brief Java class
     */
    QAndroidJniObject* m_javaClass = nullptr;
};

} // namespace BusinessLayer

#endif // JAVAFRAMECAPTURE_H
