#include "NoEffectImage.h"

#include "BusinessLayer/FaceImage.h"

#include <QIcon>
#include <QImage>

namespace BusinessLayer
{

QImage NoEffectImage::apply(const FaceImage& faceImage) const
{
    return faceImage.image();
}

QIcon NoEffectImage::icon() const
{
    // TODO: resource file icon
    return QIcon();
}

} // namespace BusinessLayer
