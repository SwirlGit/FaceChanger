#include "ItemsSlider.h"

#include "_utils/Helpers/UIHelper.h"

#include <QBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QScrollArea>
#include <QVariant>

namespace
{
// Свойство "выбрана"
const char* kPropertyChecked = "isChecked";
}

ItemsSlider::ItemsSlider(Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    m_scroll(new QScrollArea(this)),
    m_items(new QButtonGroup(this)),
    m_toLeft(new QPushButton(this)),
    m_toRight(new QPushButton(this)),
    m_orientation(orientation),
    m_currentIndex(-1)
{
    setObjectName("itemsSlider");

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
    itemsLayout->addStretch();
    itemsLayout->addStretch();
    m_scroll->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    m_scroll->setLayout(itemsLayout);

    layout->addWidget(m_toLeft, 0, firstPositionAlign);
    layout->addWidget(m_scroll);
    layout->addWidget(m_toRight, 0, lastPositionAlign);
    setLayout(layout);

    connect(m_items, static_cast<void (QButtonGroup::*)(QAbstractButton*, bool)>(&QButtonGroup::buttonToggled), this,
            [this] (QAbstractButton* button, bool checked) {
        if (checked) {
            setCurrentIndex(m_items->id(button));
        }
    });

    connect(m_toLeft, &QPushButton::clicked, this, [this] () {
        const int index = currentIndex();
        if (index > 0) {
            setCurrentIndex(index - 1);
        }

    });

    connect(m_toRight, &QPushButton::clicked, this, [this] () {
        const int tabsSize = m_items->buttons().size();
        const int index = currentIndex();
        if (index < tabsSize - 1) {
            setCurrentIndex(index + 1);
        }
    });
}

int ItemsSlider::currentIndex()
{
    return m_currentIndex;
}

void ItemsSlider::setupItemsIcons(const QVector<QIcon> &icons)
{
    for (int i = 0; i < icons.size(); ++i) {
        QPushButton* button = new QPushButton(m_scroll);
        button->setIconSize(button->size());
        button->setIcon(icons[i]);
        button->setCheckable(true);
        m_items->addButton(button, i);
        itemsLayout()->insertWidget(itemsLayout()->count() - 1, button);
    }
    if (icons.size() > 0) {
        setCurrentIndex(0);
    }
}

QBoxLayout* ItemsSlider::itemsLayout()
{
    return qobject_cast<QBoxLayout*>(m_scroll->layout());
}

void ItemsSlider::setCurrentIndex(int index)
{
    if ((index < 0) || (index >= m_items->buttons().size())) {
        Q_ASSERT_X(false, "ItemsSlider::setCurrentIndex", "invalidIndex");
        return;
    }

    if (m_currentIndex >= 0 && m_currentIndex < m_items->buttons().size()) {
        m_items->button(m_currentIndex)->setChecked(false);
        m_items->button(m_currentIndex)->setProperty(kPropertyChecked, false);
    }
    m_items->button(index)->setChecked(true);
    m_items->button(index)->setProperty(kPropertyChecked, true);
    m_currentIndex = index;
    UIHelper::refreshStyleSheet(this);
    emit currentIndexChanged(m_currentIndex);
}
