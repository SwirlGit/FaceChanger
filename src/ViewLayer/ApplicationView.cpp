#include "ApplicationView.h"
#include "ApplicationViewPrivate.h"

#include "_utils/Widgets/ItemsSlider/ItemsSlider.h"

#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>

namespace ViewLayer
{

ApplicationViewPrivate::ApplicationViewPrivate(QWidget* parent) :
    effects(new ItemsSlider(Qt::Horizontal, parent))
{
}

// ****

ApplicationView::ApplicationView(QWidget* parent) :
    QWidget(parent),
    m_pimpl(new ApplicationViewPrivate(this))
{
    setObjectName("applicationView");

    QHBoxLayout* itemsSliderLayout = new QHBoxLayout;
    itemsSliderLayout->addStretch();
    itemsSliderLayout->addWidget(m_pimpl->effects);
    itemsSliderLayout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addStretch();
    layout->addLayout(itemsSliderLayout);
    setLayout(layout);

    connect(m_pimpl->effects, SIGNAL(currentIndexChanged(int)), this, SIGNAL(currentEffectIndexChanged(int)));
}

ApplicationView::~ApplicationView()
{
    if (m_pimpl != nullptr) {
        m_pimpl.release();
    }
}

void ApplicationView::setupEffectsIcons(const QVector<QIcon>& effectsIcons)
{
    m_pimpl->effects->setupItemsIcons(effectsIcons);
}

void ApplicationView::updateImage(const QImage& image)
{
    m_imageToDraw = image;
    repaint();
}

void ApplicationView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(contentsRect(), m_imageToDraw);
    event->accept();
}

} // namespace ViewLayer
