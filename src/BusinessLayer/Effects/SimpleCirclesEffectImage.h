#ifndef SIMPLECIRCLESEFFECTIMAGE_H
#define SIMPLECIRCLESEFFECTIMAGE_H

#include "BusinessLayer/EffectImage.h"
#include "BusinessLayer/IconItem.h"

class QIcon;
class QImage;
class QPen;

namespace BusinessLayer
{
class FaceImage;

/**
 * @brief Класс эффекта с простыми кругами
 */
class SimpleCirclesEffectImage : public IEffectImage, public IIconItem
{
public:
    ~SimpleCirclesEffectImage() override final;

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

#endif // SIMPLECIRCLESEFFECTIMAGE_H
