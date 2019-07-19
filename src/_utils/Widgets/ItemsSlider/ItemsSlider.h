#ifndef ITEMSSLIDER_H
#define ITEMSSLIDER_H

#include <QWidget>

class QBoxLayout;
class QButtonGroup;
class QPushButton;
class QScrollArea;

class ItemsSlider : public QWidget
{
    Q_OBJECT

public:
    ItemsSlider(Qt::Orientation orientation = Qt::Horizontal, QWidget* parent = nullptr);

    /**
     * @brief Текущий выделенный элемент, если элементов нет - возвращает -1
     */
    int currentIndex();

    /**
     * @brief Установить иконки
     */
    void setupItemsIcons(QVector<QIcon> &icons);

signals:
    /**
     * @brief Изменился выбранный элемент
     */
    void currentIndexChanged(int index);

private:
    /**
     * @brief Layout элементов
     */
    QBoxLayout* itemsLayout();

private:

    /**
     * @brief Зона прокрутки
     */
    QScrollArea* m_scroll = nullptr;

    /**
     * @brief Элементы в виде таббара
     */
    QButtonGroup* m_items = nullptr;

    /**
     * @brief Прокрутка влево
     */
    QPushButton* m_toLeft = nullptr;

    /**
     * @brief Прокрутка вправо
     */
    QPushButton* m_toRight = nullptr;

    /**
     * @brief Ориентация в пространстве
     */
    Qt::Orientation m_orientation;

    /**
     * @brief Текущий выбранный элемент
     */
    int m_currentIndex;
};

#endif // ITEMSSLIDER_H
