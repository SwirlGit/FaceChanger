#include "ApplicationManager.h"

#include "Application.h"

#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/Effects/NoEffectImage.h"
#include "BusinessLayer/FaceImage.h"
#include "BusinessLayer/FaceImageCreator.h"
#include "BusinessLayer/FrameCreator.h"
#include "ViewLayer/ApplicationView.h"

#include <QIcon>
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
    m_frameCreator = new BusinessLayer::OpenCVFrameCreator(0, 30);
    QThread frameCreatorThread;
    m_frameCreator->moveToThread(&frameCreatorThread);
    connect(m_frameCreator, &BusinessLayer::IFrameCreator::frameCaptured,
            this, ApplicationManager::processFrame);
    connect(&frameCreatorThread, &QThread::started,
            m_frameCreator, &BusinessLayer::IFrameCreator::start);

    // настраиваем набор эффектов
    initEffects();

    // запускаем получатель изображений
    frameCreatorThread.start();
}

ApplicationManager::~ApplicationManager() = default;

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

    m_view->setupEffectsIcons(icons);
}

void ApplicationManager::processFrame(const QImage& frame)
{
    const QImage image = m_effects.at(m_currentEffect)->apply(m_faceImageCreator->createFaceImage(frame));
    m_view->updateImage(image);
}

} // namespace ManagementLayer
