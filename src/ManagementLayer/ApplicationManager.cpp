#include "ApplicationManager.h"

#include "Application.h"

#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/Effects/NoEffectImage.h"
#include "BusinessLayer/Effects/SimpleCirclesEffectImage.h"
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
    m_frameCreatorThread = new QThread;
    m_frameCreator->moveToThread(m_frameCreatorThread);
    connect(m_frameCreator, SIGNAL(frameCaptured(const QImage&)),
            this, SLOT(processFrame(const QImage&)));
    connect(m_frameCreatorThread, &QThread::started,
            m_frameCreator, &BusinessLayer::IFrameCreator::start);

    // настраиваем набор эффектов
    initEffects();

    // запускаем получатель изображений
    m_frameCreatorThread->start();
}

ApplicationManager::~ApplicationManager()
{
    m_frameCreatorThread->exit();
    delete m_frameCreator;
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

} // namespace ManagementLayer
