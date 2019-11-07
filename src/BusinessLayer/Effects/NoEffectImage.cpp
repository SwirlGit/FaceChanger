#include "NoEffectImage.h"

#include "BusinessLayer/FaceImage.h"

#include <QIcon>
#include <QImage>

namespace BusinessLayer
{

NoEffectImage::~NoEffectImage()
{
}

QImage NoEffectImage::apply(const FaceImage& faceImage) const
{
    return faceImage.image();
}

QIcon NoEffectImage::icon() const
{
    return QIcon(":/Graphics/Icons/Effects/no.svg");
}

} // namespace BusinessLayer
