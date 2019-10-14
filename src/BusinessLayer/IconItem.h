#ifndef IICONITEM_H
#define IICONITEM_H

class QIcon;

/**
 * @brief Интерфейс для классов имеющих иконку
 */
class IIconItem
{
public:
    /**
     * @brief Получить иконку изображения
     */
    virtual QIcon icon() const;
};

#endif // IICONITEM_H
