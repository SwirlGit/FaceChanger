#include "SimpleCirclesEffectImage.h"

#include "BusinessLayer/FaceImage.h"

#include <QIcon>
#include <QImage>
#include <QPainter>

namespace BusinessLayer
{

SimpleCirclesEffectImage::~SimpleCirclesEffectImage()
{
}

QImage SimpleCirclesEffectImage::apply(const FaceImage& faceImage) const
{
    QImage image = faceImage.image();
    QPainter painter(&image);
    painter.setPen(Qt::blue);

    for (const Face& face: faceImage.faces()) {
        painter.drawEllipse(face.center(), face.radius(), face.radius());
        if (face.hasLeftEye()) {
            const Eye& leftEye = face.leftEye();
            painter.drawEllipse(leftEye.center(), leftEye.radius(), leftEye.radius());
        }
        if (face.hasRightEye()) {
            const Eye& rightEye = face.rightEye();
            painter.drawEllipse(rightEye.center(), rightEye.radius(), rightEye.radius());
        }
    }

    return image;
}

QIcon SimpleCirclesEffectImage::icon() const
{
    return QIcon(":/Graphics/Icons/Effects/simple-circles.svg");
}

} // namespace BusinessLayer
