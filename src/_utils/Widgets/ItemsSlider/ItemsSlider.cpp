#include "ItemsSlider.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QScrollArea>
#include <QBoxLayout>

ItemsSlider::ItemsSlider(Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    m_scroll(new QScrollArea(this)),
    m_items(new QButtonGroup(this)),
    m_toLeft(new QPushButton(this)),
    m_toRight(new QPushButton(this)),
    m_orientation(orientation),
    m_currentIndex(-1)
{
    QBoxLayout* layout;
    QBoxLayout* itemsLayout;
    Qt::AlignmentFlag firstPositionAlign;
    Qt::AlignmentFlag lastPositionAlign;
    if (m_orientation == Qt::Horizontal) {
        layout = new QHBoxLayout;
        itemsLayout = new QHBoxLayout;
        firstPositionAlign = Qt::AlignLeft;
        lastPositionAlign = Qt::AlignRight;
    } else {
        layout = new QVBoxLayout;
        itemsLayout = new QVBoxLayout;
        firstPositionAlign = Qt::AlignTop;
        lastPositionAlign = Qt::AlignBottom;
    }
    m_scroll->setLayout(itemsLayout);

    layout->addWidget(m_toLeft, 0, firstPositionAlign);
    layout->addWidget(m_scroll);
    layout->addWidget(m_toRight, 0, lastPositionAlign);
    setLayout(layout);

    connect(m_items, static_cast<void (QButtonGroup::*)(QAbstractButton*, bool)>(&QButtonGroup::buttonToggled), this,
            [this] (QAbstractButton* button, bool checked) {
        if (checked) {
            button->setChecked(checked);
            emit currentIndexChanged(currentIndex());
        }
    });

    connect(m_toLeft, &QPushButton::clicked, this, [this] () {
        const int tabsSize = m_items->buttons().size();
        const int nextButtonIndex = (currentIndex() == 0) ? tabsSize - 1 : currentIndex() - 1;
        m_items->button(nextButtonIndex)->setChecked(true);
    });

    connect(m_toRight, &QPushButton::clicked, this, [this] () {
        const int tabsSize = m_items->buttons().size();
        const int nextButtonIndex = (currentIndex() >= tabsSize - 1) ? 0 : currentIndex() + 1;
        m_items->button(nextButtonIndex)->setChecked(true);
    });
}

int ItemsSlider::currentIndex()
{
    return itemsLayout()->indexOf(m_items->checkedButton());
}

void ItemsSlider::setupItemsIcons(const QVector<QIcon> &icons)
{
    for (int i = 0; i < icons.size(); ++i) {
        QPushButton* button = new QPushButton(m_scroll);
        button->setIcon(icons[i]);
        button->setCheckable(true);
        m_items->addButton(button);
        itemsLayout()->insertWidget(itemsLayout()->count() - 1, button);
    }
}

QBoxLayout* ItemsSlider::itemsLayout()
{
    return qobject_cast<QBoxLayout*>(m_scroll->layout());
}
