#include "OpenCVFrameCreator.h"

#include "_utils/Helpers/CVHelper.h"

#include <QDateTime>
#include <QDebug>
#include <QImage>
#include <QTimer>

#include <opencv2/videoio/videoio.hpp>

using namespace cv;

namespace BusinessLayer
{

namespace
{
// перерыв до следующей попытки захватить устройство
const int kDefaultOpenDeviceRetryTimeout = 1000; // мс
// коэффициент seconds -> ms
const int kSecToMs = 1000;
}

OpenCVFrameCreator::OpenCVFrameCreator(int cameraIndex, int fps, QObject *parent) :
    IFrameCreator(parent),
    m_videoCapture(new VideoCapture(cameraIndex, CAP_ANY)),
    m_cameraIndex(cameraIndex),
    m_captureTimeoutMs(kSecToMs / fps)
{
}

OpenCVFrameCreator::~OpenCVFrameCreator()
{
    m_videoCapture->release();
}

void OpenCVFrameCreator::start()
{
    const qint64 timeAtStartMs = QDateTime::currentMSecsSinceEpoch();

    // Если устройство не захвачено, сообщаем об этом, пытаемся захватить и планируем повтор через секунду
    if (!m_videoCapture->isOpened()) {
        m_videoCapture->open(m_cameraIndex, CAP_ANY);
        static const QString errorString = "Video device is not opened, can not capture frame";
        qDebug() << errorString;
        QTimer::singleShot(kDefaultOpenDeviceRetryTimeout, this, SLOT(start()));
        return;
    }

    // Получаем изображение
    if (m_videoCapture->grab()) {
        Mat frame;
        m_videoCapture->retrieve(frame);
        emit frameCaptured(CVHelper::MatToQImage(frame));
    }

    // Планируем следующий вызов исходя из установленного fps и потраченного времени
    QTimer::singleShot(static_cast<int>(m_captureTimeoutMs - (QDateTime::currentMSecsSinceEpoch() - timeAtStartMs)),
                       this, SLOT(start()));
}

} // namespace BusinessLayer
