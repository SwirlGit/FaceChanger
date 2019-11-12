#include "ApplicationManager.h"

#include "Application.h"

#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/Effects/NoEffectImage.h"
#include "BusinessLayer/Effects/SimpleCirclesEffectImage.h"
#include "BusinessLayer/FaceImage.h"
#include "BusinessLayer/FaceImageCreator.h"
#include "BusinessLayer/FrameCapture.h"
#include "BusinessLayer/FrameCaptures/OpenCVFrameCapture.h"
#include "ViewLayer/ApplicationView.h"

#include <QIcon>
#include <QImage>
#include <QThread>

using ViewLayer::ApplicationView;

namespace ManagementLayer
{

ApplicationManager::ApplicationManager(QObject* parent) :
    QObject(parent),
    m_view(new ApplicationView)
{
    // настраиваем определителя лица на изображениях
    m_faceImageCreator = new BusinessLayer::OpenCVFaceImageCreator();

    // настраиваем ресивер изображений
    m_frameCapture = new BusinessLayer::OpenCVFrameCapture(0, 30);
    m_frameCaptureThread = new QThread;
    m_frameCapture->moveToThread(m_frameCaptureThread);
    connect(m_frameCapture, SIGNAL(frameCaptured(const QImage&)),
            this, SLOT(processFrame(const QImage&)));
    connect(m_frameCaptureThread, &QThread::started,
            m_frameCapture, &BusinessLayer::IFrameCapture::start);

    // настраиваем набор эффектов
    initEffects();

    // настраиваем взаимодействие со view
    connect(m_view.get(), SIGNAL(currentEffectIndexChanged(int)),
            this, SLOT(setCurrentEffect(int)));

    // запускаем получатель изображений
    m_frameCaptureThread->start();
}

ApplicationManager::~ApplicationManager()
{
    m_frameCaptureThread->exit();
    delete m_frameCapture;
    delete m_faceImageCreator;
    qDeleteAll(m_effects);
    m_view.release();
}

QWidget* ApplicationManager::view() const
{
    return m_view.get();
}

void ApplicationManager::exec()
{
    m_view->showMaximized();
}

void ApplicationManager::initEffects()
{
    QVector<QIcon> icons;

    // Пустой эффект
    BusinessLayer::NoEffectImage* noEffectImage = new BusinessLayer::NoEffectImage();
    m_effects.append(noEffectImage);
    icons.append(noEffectImage->icon());

    // Эффект с простыми кругами
    BusinessLayer::SimpleCirclesEffectImage* simpleCirclesEffectImage = new BusinessLayer::SimpleCirclesEffectImage();
    m_effects.append(simpleCirclesEffectImage);
    icons.append(simpleCirclesEffectImage->icon());

    m_view->setupEffectsIcons(icons);
}

void ApplicationManager::processFrame(const QImage& frame)
{
    const QImage image = m_effects.at(m_currentEffect)->apply(m_faceImageCreator->createFaceImage(frame));
    m_view->updateImage(image);
}

void ApplicationManager::setCurrentEffect(int index)
{
    m_currentEffect = index;
}

} // namespace ManagementLayer
