#include "JavaFrameCapture.h"

#include <QImage>
#include <QtAndroidExtras>
#include <QAndroidJniObject>

namespace {
JNIEXPORT void JNICALL
javaframecapture_imageCaptured(JNIEnv*/*env*/, jobject /*obj*/, jbyteArray buf, jint width, jint height)
{
    QAndroidJniEnvironment env;
    int len = env->GetArrayLength(buf);
    QByteArray array;
    array.resize(len);
    env->GetByteArrayRegion(buf, 0, len, reinterpret_cast<jbyte*>(array.data()));
    QImage image = QImage((const uchar*)array.data(), width, height, QImage::Format_RGB888);
}
}

namespace BusinessLayer {

JavaFrameCapture::JavaFrameCapture(QObject *parent) : IFrameCapture(parent)
{
}

JavaFrameCapture::~JavaFrameCapture()
{

}

void JavaFrameCapture::start()
{
    QAndroidJniObject::callStaticMethod<void>("javaframecapture/JavaFrameCapture", "captureAnImage", "()V");
}

} // namespace BusinessLayer
