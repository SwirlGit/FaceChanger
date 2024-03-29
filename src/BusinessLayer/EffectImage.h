#ifndef EFFECTIMAGE_H
#define EFFECTIMAGE_H

class QImage;

namespace BusinessLayer
{
class FaceImage;

/**
 * @brief Интерфейс эффектов
 */
class IEffectImage
{
public:
    virtual ~IEffectImage() = default;

    /**
     * @brief Применить эффект
     */
    virtual QImage apply(const FaceImage& faceImage) const = 0;
};

}
#endif // EFFECTIMAGE_H
