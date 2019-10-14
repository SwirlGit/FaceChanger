#include "ApplicationManager.h"

#include "Application.h"

#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/FaceImage.h"
#include "BusinessLayer/FaceImageCreator.h"
#include "BusinessLayer/FrameCreator.h"
#include "ViewLayer/ApplicationView.h"

#include <QThread>

using BusinessLayer::EffectImage;
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
    m_frameCreator = new BusinessLayer::OpenCVFrameCreator(0, 30, this);
    QThread frameCreatorThread;
    m_frameCreator->moveToThread(&frameCreatorThread);
    connect(m_frameCreator, &BusinessLayer::IFrameCreator::frameCaptured,
            this, ApplicationManager::processFrame);
    connect(&frameCreatorThread, &QThread::started,
            m_frameCreator, &BusinessLayer::IFrameCreator::start);

    // настраиваем набор эффектов
    // TODO: m_effects.append(new EffectImageSomething())
    // m_view->setupEffectsIcons(icons);

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

void ApplicationManager::processFrame(const QImage& frame)
{
    Q_UNUSED(frame);
    const QImage image;// = m_effects.at(currentEffect)->apply(m_faceImageCreator->createFaceImage(frame));
    m_view->updateImage(image);
}

} // namespace ManagementLayer
