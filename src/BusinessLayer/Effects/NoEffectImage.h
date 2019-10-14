#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/IconItem.h"

class QIcon;
class QImage;

namespace BusinessLayer
{
class FaceImage;

/**
 * @brief Класс пустого эффекта
 */
class NoEffectImage : public IEffectImage, public IIconItem
{
public:
    ~NoEffectImage() override final;

    /**
     * @brief Применить эффект
     */
    QImage apply(const FaceImage& faceImage) const override final;

    /**
     * @brief Получить иконку эффекта
     */
    QIcon icon() const override final;
};

} // namespace BusinessLayer
