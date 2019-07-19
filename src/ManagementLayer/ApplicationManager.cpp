#include "ApplicationManager.h"

#include "Application.h"

#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/FaceImage.h"
#include "ViewLayer/ApplicationView.h"

using ManagementLayer::ApplicationManager;
using ViewLayer::ApplicationView;

ApplicationManager::ApplicationManager(QObject* parent) :
    QObject(parent),
    m_view(new ApplicationView)
{
    //TODO: m_effects.append(new EffectImageSomething())
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

void ApplicationManager::processFrame()
{

}
