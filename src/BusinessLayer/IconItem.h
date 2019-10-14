#ifndef IICONITEM_H
#define IICONITEM_H

class QIcon;

namespace BusinessLayer
{

/**
 * @brief Интерфейс для классов имеющих иконку
 */
class IIconItem
{
public:
    virtual ~IIconItem() = default;

    /**
     * @brief Получить иконку изображения
     */
    virtual QIcon icon() const = 0;
};

} // namespace BusinessLayer

#endif // IICONITEM_H
