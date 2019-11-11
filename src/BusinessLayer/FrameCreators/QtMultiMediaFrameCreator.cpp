#include "QtMultiMediaFrameCreator.h"

#include <QDateTime>
#include <QDebug>
#include <QImage>
#include <QTimer>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimedia/QCameraInfo>

namespace
{
// коэффициент seconds -> ms
const int kSecToMs = 1000;
}

namespace BusinessLayer {

QtMultiMediaFrameCreator::QtMultiMediaFrameCreator(int fps, QObject* parent) :
    IFrameCreator(parent),
    m_captureTimeoutMs(kSecToMs / fps)
{
    if (QCameraInfo::availableCameras().count() < 1) {
        qDebug() << "have no available cameras";
        return;
    }
    setCamera(QCameraInfo::defaultCamera());
}

QtMultiMediaFrameCreator::~QtMultiMediaFrameCreator()
{

}

void QtMultiMediaFrameCreator::start()
{
    const qint64 timeAtStartMs = QDateTime::currentMSecsSinceEpoch();

    m_camera->searchAndLock();
    //if (m_imageCapture->isReadyForCapture()) {
    //    m_imageCapture->capture();
    //}
    m_camera->unlock();

    // Планируем следующий вызов исходя из установленного fps и потраченного времени
    //QTimer::singleShot(static_cast<int>(m_captureTimeoutMs - (QDateTime::currentMSecsSinceEpoch() - timeAtStartMs)),
    //                   this, SLOT(start()));
}

void QtMultiMediaFrameCreator::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera = new QCamera(cameraInfo);
    connect(m_camera, SIGNAL(statusChanged(QCamera::Status)), this, SLOT(processStatus(QCamera::Status)));
    m_camera->load();
}

void QtMultiMediaFrameCreator::startCamera()
{
    m_camera->setCaptureMode(QCamera::CaptureMode::CaptureStillImage);
    m_imageCapture = new QCameraImageCapture(m_camera);
    if(!m_imageCapture->isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer))
        {
            qDebug() << "Can't take data frome camera into buffer";
        }
    m_imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    connect(m_imageCapture, SIGNAL(readyForCaptureChanged(bool)), this, SLOT(captureReady(bool)));
    connect(m_imageCapture, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(processCapturedImage(int, const QImage&)));
    m_camera->start();
}

void QtMultiMediaFrameCreator::processCapturedImage(int requestId, const QImage& image)
{
    Q_UNUSED(requestId);
    emit frameCaptured(image);
}

void QtMultiMediaFrameCreator::captureReady(bool ready)
{
    if (ready) {
        //m_camera->searchAndLock();
        //m_imageCapture->capture();
        //m_camera->unlock();
    }
}

void QtMultiMediaFrameCreator::processStatus(QCamera::Status status)
{
    switch (status)
        {
        case QCamera::ActiveStatus:

            qInfo() << "The camera has been started and can produce data.";

            break;

        case QCamera::StartingStatus:

            qInfo() << "The camera is starting.";

            break;

        case QCamera::StoppingStatus:

            qInfo() << "The camera is stopping.";

            break;

        case QCamera::StandbyStatus:

            qInfo() << "The camera is in the power saving standby mode.";

            break;

        case QCamera::LoadedStatus:

            qInfo() << "The camera is loaded and ready to be configured.";
            startCamera();

            break;

        case QCamera::LoadingStatus:

            qInfo() << "The camera device loading.";

            break;

        case QCamera::UnloadingStatus:

            qInfo() << "The camera device is unloading.";

            break;

        case QCamera::UnloadedStatus:

            qInfo() << "The initial camera status, with camera not loaded.";

            break;

        case QCamera::UnavailableStatus:

            qInfo() << "The camera or camera backend is not available.";

            break;
        }
}

} // namespace BusinessLayer
