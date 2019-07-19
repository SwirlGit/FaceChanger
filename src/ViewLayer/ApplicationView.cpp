#include "ApplicationView.h"
#include "ApplicationViewPrivate.h"

//#include <QApplication>

using ViewLayer::ApplicationViewPrivate;
using ViewLayer::ApplicationView;


ApplicationViewPrivate::ApplicationViewPrivate()
{
}

// ****

ApplicationView::ApplicationView(QWidget *parent) :
    QWidget(parent),
    m_pimpl(new ApplicationViewPrivate)
{
    setObjectName("applicationView");
}

ApplicationView::~ApplicationView()
{

}
