#include "ApplicationView.h"
#include "ApplicationViewPrivate.h"

namespace ViewLayer
{

ApplicationViewPrivate::ApplicationViewPrivate()
{
}

// ****

ApplicationView::ApplicationView(QWidget* parent) :
    QWidget(parent),
    m_pimpl(new ApplicationViewPrivate)
{
    setObjectName("applicationView");

    //TODO:
    //connect(m_pimpl->effectsWidget, &EffectsWidget::currentIndexChanged, this, &ApplicationView::currentEffectIndexChanged);
}

ApplicationView::~ApplicationView()
{
}

void ApplicationView::setupEffectsIcons(const QVector<QIcon>& effectsIcons)
{
    //TODO:
    //m_pimpl->effectsWidget->setIcons(effectsIcons);
}

void ApplicationView::updateImage(const QImage& image)
{
    //TODO:
    //m_pimpl->mainFrame->setImage(image);
}

} // namespace ViewLayer
