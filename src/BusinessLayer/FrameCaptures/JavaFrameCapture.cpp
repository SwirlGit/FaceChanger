#include "JavaFrameCapture.h"

#include <QImage>
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QDebug>

namespace {
static void imageCaptured(JNIEnv*/*env*/, jobject /*obj*/, jbyteArray buf, jint width, jint height)
{
    /*QAndroidJniEnvironment env;
    int len = env->GetArrayLength(buf);
    QByteArray array;
    array.resize(len);
    env->GetByteArrayRegion(buf, 0, len, reinterpret_cast<jbyte*>(array.data()));
    QImage image = QImage((const uchar*)array.data(), width, height, QImage::Format_RGB888);*/
    qDebug() << "we are in";
}
}

namespace BusinessLayer {

JavaFrameCapture::JavaFrameCapture(QObject *parent) : IFrameCapture(parent)
{
    m_javaClass = new QAndroidJniObject ("com/javaframecapture/FrameCapture",
                                         "(Landroid/content/Context;Landroid/app/Activity;)V",
                                         QtAndroid::androidContext().object<jobject>(),
                                         QtAndroid::androidActivity().object<jobject>());

    JNINativeMethod methods[] = {
           {"imageCaptured", "([B;I;I)V", reinterpret_cast<void*>(imageCaptured)}};

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(m_javaClass->object<jobject>());
    env->RegisterNatives(objectClass, methods, sizeof (methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

JavaFrameCapture::~JavaFrameCapture()
{

}

void JavaFrameCapture::start()
{
    m_javaClass->callMethod<void>("captureAnImage");
}

} // namespace BusinessLayer
